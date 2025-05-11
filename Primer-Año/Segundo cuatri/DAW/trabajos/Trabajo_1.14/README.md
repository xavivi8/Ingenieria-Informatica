# 1.14 Uso de Criteria Api

##  Autores
* José Pedrajas de la Torre
* Pedro Jesús Cros Pérez
* Fco. Javier Martín-Lunas Escobar

## Descripción breve
Dentro de JPA, la Criteria API es el módulo que te permite armar consultas de forma fluida y tipada usando sólo código Java: en vez de escribir cadenas JPQL, vas encadenando objetos (CriteriaBuilder, CriteriaQuery, Root, predicados) que representan cada parte de la sentencia; el compilador valida nombres de atributos, el IDE sugiere autocompletado y puedes añadir filtros, ordenar o paginar dinámicamente sin perder portabilidad entre motores de base de datos


## Bibliografía y referencias

- [Medium*](https://medium.com/@danaprata/jpa-criteria-api-quick-intro-6f2ce2462ee1)
- [Baeldung](https://www.baeldung.com/hibernate-criteria-queries)
- [Arquitectura Java](https://www.arquitecturajava.com/jpa-criteria-api-un-enfoque-diferente/)
- [JakartaEE](https://jakarta.ee/learn/docs/jakartaee-tutorial/current/persist/persistence-string-queries/persistence-string-queries.html)
- [Tutorials Point](https://www.tutorialspoint.com/es/jpa/jpa_criteria_api.htm)

## Inteligencias Artificales Generativas empleadas

- ChatGPT ⇒ o3
- GitHub Copilot. Adaptar código.
- Perplexity. Generación de código.

## Materiales complementarios

### Ejemplo 1
#### deleteUser(Long id)
##### 1. Propósito del método deleteUser(Long id)

`deleteUser(Long id)` borra **todas las nóminas** (`Payslip`) asociadas al usuario y, después, **elimina la propia entidad** `User`.
Se apoya en la **Criteria API** para lanzar un *bulk delete* eficiente sobre la tabla de nóminas y solo recurre a `em.remove()` cuando necesita la lógica de ciclo de vida de la entidad `User`.

---

##### 2. Flujo de ejecución

| Paso    | Fragmento de código | Explicación|
| ------- | -------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------ |
| **2.1** | `CriteriaBuilder cb = em.getCriteriaBuilder();`| La fábrica de la Criteria API.|
| **2.2** | `CriteriaDelete<Payslip> del = cb.createCriteriaDelete(Payslip.class);`<br>`Root<Payslip> root = del.from(Payslip.class);` | Define un *DELETE* sobre la entidad `Payslip` y crea su “alias” (`root`). |
| **2.3** | `del.where(cb.equal(root.get("userID"), id));` | Construye el *Predicate* que filtra por el `id` recibido.|
| **2.4** | `em.createQuery(del).executeUpdate();`| Ejecuta un único **bulk delete** en la BD. No se cargan entidades en memoria|
| **2.5** | `User user = em.find(User.class, id);`<br>`if (user != null) em.remove(user);` | Recupera la entidad `User` y la elimina con `remove`, disparando callbacks, cascadas, etc. |
| **2.6** | `catch (Exception ex) { logger.log(...); }`| Registra cualquier error sin propagar alcontenedor.|

#### login(String email, String password) 
##### 1. Propósito del método (login)

`login(String email, String password)` verifica si existe al menos un `User` cuyo `email` y `password` coincidan con los parámetros recibidos. Devuelve `true` cuando la autenticación es correcta y `false` en caso contrario o ante cualquier error.

---

##### 2. Flujo de ejecución (login)

| Paso | Fragmento de código | Explicación |
|------|---------------------|-------------|
| **2.1** | `CriteriaBuilder cb = em.getCriteriaBuilder();` | Fábrica de la Criteria API. |
| **2.2** | `CriteriaQuery<Long> cq = cb.createQuery(Long.class);` | Define una consulta que devuelve un `Long`. |
| **2.3** | `Root<User> root = cq.from(User.class);` | Crea el alias principal sobre la entidad `User`. |
| **2.4** | `Predicate emailPredicate = cb.equal(root.get("email"), email);`<br>`Predicate passwordPredicate = cb.equal(root.get("password"), password);` | Predicados de igualdad para `email` y `password`. |
| **2.5** | `cq.select(cb.count(root)).where(cb.and(emailPredicate, passwordPredicate));` | Selecciona el número de registros que cumplen ambas condiciones. |
| **2.6** | `TypedQuery<Long> query = em.createQuery(cq);`<br>`Long count = query.getSingleResult();` | Ejecuta la consulta y obtiene la cuenta. |
| **2.7** | `return count != null && count > 0;` | Devuelve `true` si existe al menos un usuario válido. |
| **2.8** | `catch (Exception ex) { logger.log(...); return false; }` | Maneja la excepción, registra el error y devuelve `false`. |

### Ejemplo 2

#### getAllPayslips()
##### 1. Propósito del método (getAllPayslips)

`getAllPayslips()` recupera y devuelve una **lista completa de nóminas** (`Payslip`) almacenadas en la base de datos. Sirve como método de lectura general; ante cualquier error registra la excepción y devuelve `null` (o una lista vacía).

---

##### 2. Flujo de ejecución (getAllPayslips)

| Paso | Fragmento de código | Explicación |
|------|---------------------|-------------|
| **2.1** | `CriteriaBuilder cb = em.getCriteriaBuilder();` | Fábrica de la Criteria API. |
| **2.2** | `CriteriaQuery<Payslip> cq = cb.createQuery(Payslip.class);` | Crea una consulta que devolverá objetos `Payslip`. |
| **2.3** | `Root<Payslip> root = cq.from(Payslip.class);`<br>`cq.select(root);` | Define el alias principal (`root`) y selecciona todas sus columnas. |
| **2.4** | `payslips = em.createQuery(cq).getResultList();` | Ejecuta la consulta y obtiene la lista de resultados. |
| **2.5** | `catch (Exception e) { logger.log(...); }` | Maneja la excepción, registra el error y sigue la ejecución retornando `payslips` (posiblemente `null`). |

#### deletePayslipsByStatus(PayslipStatus status)
##### 1. Propósito del método (deletePayslipsByStatus)

`deletePayslipsByStatus(PayslipStatus status)` borra **todas las nóminas** (`Payslip`) cuyo campo `status` coincide con el valor recibido.  
Aprovecha un *bulk delete* de la Criteria API para realizar la operación en una sola sentencia SQL y, al finalizar, muestra por consola cuántos registros fueron eliminados.

---

##### 2. Flujo de ejecución (deletePayslipsByStatus)

| Paso | Fragmento de código | Explicación |
|------|---------------------|-------------|
| **2.1** | `CriteriaBuilder cb = em.getCriteriaBuilder();` | Fábrica de la Criteria API. |
| **2.2** | `CriteriaDelete<Payslip> del = cb.createCriteriaDelete(Payslip.class);`<br>`Root<Payslip> root = del.from(Payslip.class);` | Define un `DELETE` sobre la entidad `Payslip` y crea el alias principal. |
| **2.3** | `del.where(cb.equal(root.get("status"), status));` | Construye el `Predicate` que filtra por el estado indicado. |
| **2.4** | `int deleted = em.createQuery(del).executeUpdate();` | Ejecuta el *bulk delete* y devuelve el número de filas afectadas. |
| **2.5** | `System.out.println("Nóminas eliminadas: " + deleted);` | Imprime en consola la cantidad de nóminas eliminadas. |

- Bulk
    - Bulk (en JPA/SQL) es una operación masiva que afecta a muchas filas con una sola sentencia (DELETE, UPDATE o INSERT), sin cargar cada entidad en memoria; se ejecuta directamente en la base de datos para mayor eficiencia.