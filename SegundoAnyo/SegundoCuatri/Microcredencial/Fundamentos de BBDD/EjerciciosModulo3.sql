USE sakila;

## Ejercicios basicos

# Ejercicio 1
#  nom y apell de cada actor en una unica tabla actor

SELECT first_name, last_name FROM actor;

# Ejercicio 2
#  muestra nom y appe de cada actor en una unica columna en letras mayusculas, nombre de la columna "Actor Name"

SELECT UPPER(CONCAT(first_name, ' ', last_name)) AS `Actor Name` FROM actor;

# Ejercicio 3
# primeros 20 registros de la tabla payment

SELECT * FROM payment LIMIT 20;

# Ejercicio 4 
# encontrar ID, nombre, apell de un actor, el actor es Joe

SELECT actor_id, first_name, last_name FROM actor WHERE first_name = 'Joe';

# Ejercicio 5
# muestra todos los apellidos distintos que hay en la tabla actor

SELECT DISTINCT last_name FROM actor;

# Ejercicio 6
# muestra titulo, desc, long y rating para las peliculas de mas de tres horas

SELECT title, description, length, rating FROM film WHERE length > 180;

# Ejercicio 7
# columnas de la tabla customer para registros donde el cliente este inactivo o acabe en "M"

SELECT * FROM customer WHERE active = 0 OR last_name LIKE '%M';

## IN, BETWEEN, LIKE, ORDER BY

# Ejercicio 8
# 

SELECT first_name, last_name FROM actor WHERE last_name LIKE '%GEN%';

# Ejercicio 9
#

SELECT first_name, last_name FROM actor WHERE last_name LIKE '%LI%' ORDER BY last_name ASC, first_name ASC;

# Ejercicio 10
#

SELECT title, description, release_year FROM film WHERE title LIKE 'A Thoughtful%';


# Ejercicio 11
#

SELECT title, description, rental_duration FROM film WHERE description LIKE '%Boat%';

# Ejercicio 12
#

SELECT * FROM film ORDER BY length ASC;

# Ejercicio 13
#

SELECT DISTINCT rating FROM film ORDER BY rating DESC;

# Ejercicio 14
#

SELECT title, description, special_features, length, rental_duration
FROM film
WHERE special_features LIKE '%Behind the Scenes%'
	AND length < 120
    AND rental_duration BETWEEN 5 AND 7
ORDER BY length DESC
LIMIT 10;

## Agrupaciones y Agregaciones

# Ejercicio 15
#

SELECT last_name, COUNT(*) AS num_actores FROM actor GROUP BY last_name;

# Ejercicio 16
#

SELECT last_name, COUNT(*) AS num_actores FROM actor GROUP BY last_name HAVING COUNT(*) >= 2;

# Ejercicio 17
#

SELECT customer_id, COUNT(*) AS num_alquileres FROM rental GROUP BY customer_id;

# Ejercicio 18
#

SELECT customer_id, SUM(amount) AS total_aportado 
FROM payment 
GROUP BY customer_id 
ORDER BY total_aportado DESC
LIMIT 10;

# Ejercicio 19
#

Select MAX(amount) - MIN(amount) AS diferencia FROM payment;

# Ejercicio 20
#

SELECT customer_id, AVG(amount) AS media_por_pago FROM payment GROUP BY  customer_id;

# Ejercicio 21
#

ALTER TABLE actor ADD COLUMN middle_name VARCHAR(45) NULL AFTER first_name;

# Ejercicio 22
#

ALTER TABLE actor MODIFY COLUMN middle_name BLOB;

# Ejercicio 23
#

ALTER TABLE actor DROP COLUMN middle_name;

# Ejercicio 24
#

UPDATE actor SET first_name='HARPO' WHERE last_name='WILLIAMS' AND first_name='GROUCHO';

# Ejercicio 25
#

UPDATE actor
SET first_name = 'MUCHO GROUCHO'
WHERE actor_id IN (
	SELECT actor_id
    FROM (SELECT actor_id FROM actor WHERE first_name='GROUCHO') AS t
);

UPDATE actor
SET first_name = 'GROUCHO'
WHERE actor_id IN (
	SELECT actor_id
    FROM (SELECT actor_id FROM actor WHERE first_name='HARPO') AS t
);

## Join

# Ejercicio 26
#

SELECT s.first_name, s.last_name,
       a.address, a.address2, a.district, a.postal_code, a.phone
FROM staff AS s
JOIN address AS a ON s.address_id = a.address_id;

# Ejercicio 27
#

SELECT s.staff_id, s.first_name, s.last_name,
       SUM(p.amount) AS total_recibido
FROM staff AS s
JOIN payment AS p ON p.staff_id = s.staff_id
WHERE p.payment_date >= '2005-08-01' AND p.payment_date <  '2005-09-01'
GROUP BY s.staff_id, s.first_name, s.last_name
ORDER BY total_recibido DESC;

# Ejercicio 28
#

SELECT f.film_id, f.title, COUNT(fa.actor_id) AS num_actores
FROM film AS f
LEFT JOIN film_actor AS fa ON fa.film_id = f.film_id
GROUP BY f.film_id, f.title
ORDER BY f.title;

# Ejercicio 29
#

SELECT c.customer_id, c.first_name, c.last_name,SUM(p.amount) AS total_pagado
FROM customer AS c
JOIN payment  AS p ON p.customer_id = c.customer_id
GROUP BY c.customer_id, c.first_name, c.last_name
ORDER BY c.last_name ASC, c.first_name ASC;

# Ejercicio 30
# 

SELECT ci.city, co.country
FROM city AS ci
JOIN country AS co ON co.country_id = ci.country_id
ORDER BY co.country, ci.city;

# Subconsltas y consultas avanzadas

# Ejercicio 31
#

SELECT title
FROM film
WHERE (title LIKE 'K%' OR title LIKE 'Q%') AND language_id IN (
	SELECT language_id
    FROM language
    WHERE name IN ('English', 'French')
);

# Ejercicio 32
#

SELECT *
FROM customer
WHERE customer_id IN (
	SELECT r.customer_id
	FROM rental r
	JOIN inventory i ON i.inventory_id = r.inventory_id
	JOIN film f ON f.film_id = i.film_id
	WHERE f.title LIKE '%S%Q%L%'
);

# Ejercicio 33
#
# Sin Join

SELECT CONCAT(first_name, ' ', last_name) AS nombre_completo, email
FROM customer
WHERE address_id IN (
	SELECT address_id
	FROM address
	WHERE city_id IN (
		SELECT city_id
		FROM city
		WHERE country_id IN (
			SELECT country_id
			FROM country
			WHERE country = 'Canada'
		)
	)
);

# Con Join

SELECT CONCAT(c.first_name, ' ', c.last_name) AS nombre_completo, c.email
FROM customer c
JOIN address a ON a.address_id = c.address_id
JOIN city ci ON ci.city_id = a.city_id
JOIN country co ON co.country_id = ci.country_id
WHERE co.country = 'Canada'
ORDER BY c.last_name, c.first_name;

# Ejercicio 34
#

SELECT f.film_id, f.title, COUNT(*) AS veces_alquilada
FROM film f
JOIN inventory i ON i.film_id = f.film_id
JOIN rental r ON r.inventory_id = i.inventory_id
GROUP BY f.film_id, f.title
ORDER BY veces_alquilada DESC;

# Ejercicio 35
#

SELECT cat.name AS categoria, SUM(p.amount) AS ingresos
FROM category cat
JOIN film_category fc ON fc.category_id = cat.category_id
JOIN inventory i ON i.film_id = fc.film_id
JOIN rental r ON r.inventory_id = i.inventory_id
JOIN payment p ON p.rental_id = r.rental_id
GROUP BY cat.category_id, cat.name
ORDER BY ingresos DESC
LIMIT 5;

# Case when

# Ejercicio 36
#

SELECT film_id, title, length,
	CASE
		WHEN length < 90 THEN 'Corta'
		WHEN length BETWEEN 90 AND 180 THEN 'Media'
		ELSE 'Larga'
	END AS clasificacion
FROM film
ORDER BY length;

# Ejercicio 37
#

SELECT c.customer_id, CONCAT(c.first_name, ' ', c.last_name) AS cliente, c.email, COUNT(r.rental_id) AS num_alquileres,
	CASE
		WHEN COUNT(r.rental_id) > 30 THEN 'Frecuente'
		WHEN COUNT(r.rental_id) < 30 THEN 'Ocasional'
		ELSE 'Justo 30'
	END AS tipo_cliente
FROM customer c
LEFT JOIN rental r ON r.customer_id = c.customer_id
GROUP BY c.customer_id, c.first_name, c.last_name, c.email
ORDER BY num_alquileres DESC, cliente;

# CTEs

# Ejercicio 38
#

WITH film_cat AS (
	SELECT c.category_id, c.name AS categoria, f.length
	FROM category c
	JOIN film_category fc ON fc.category_id = c.category_id
	JOIN film f ON f.film_id = fc.film_id
)

SELECT categoria, AVG(length) AS promedio_duracion
FROM film_cat
GROUP BY categoria
ORDER BY promedio_duracion DESC;

# Ejercicio 39
#

WITH actor_films AS (
	SELECT
		a.actor_id,
		a.first_name,
		a.last_name,
		COUNT(fa.film_id) AS num_peliculas
	FROM actor a
	JOIN film_actor fa ON fa.actor_id = a.actor_id
	GROUP BY a.actor_id, a.first_name, a.last_name
)

SELECT actor_id, CONCAT(first_name, ' ', last_name) AS actor, num_peliculas
FROM actor_films
ORDER BY num_peliculas DESC, actor
LIMIT 5;

# Mas consultas avanzadas

# Ejercicio 40
#

SELECT c.customer_id, CONCAT(c.first_name, ' ', c.last_name) AS cliente, COUNT(r.rental_id) AS num_alquileres
FROM customer c
JOIN rental r ON r.customer_id = c.customer_id
GROUP BY c.customer_id, c.first_name, c.last_name
HAVING COUNT(r.rental_id) > (
	SELECT AVG(cnt)
	FROM (
		SELECT COUNT(*) AS cnt
		FROM rental
		GROUP BY customer_id
	) AS x
)
ORDER BY num_alquileres DESC;

# Ejercicio 41
#

SELECT f.film_id, f.title
FROM film f
WHERE NOT EXISTS (
	SELECT 1
	FROM inventory i
	JOIN rental r ON r.inventory_id = i.inventory_id
	WHERE i.film_id = f.film_id
)
ORDER BY f.title;

# Operaciones de ventas

# Ejercicio 42
#

WITH rentals_por_pelicula AS (
	SELECT
		i.store_id,
		f.film_id,
		f.title,
		COUNT(*) AS num_alquileres
	FROM rental r
	JOIN inventory i ON i.inventory_id = r.inventory_id
	JOIN film f ON f.film_id = i.film_id
	GROUP BY i.store_id, f.film_id, f.title
)
SELECT store_id, film_id, title, num_alquileres,
DENSE_RANK() OVER (
	PARTITION BY store_id
    ORDER BY num_alquileres DESC
) AS ranking_en_tienda
FROM rentals_por_pelicula
ORDER BY store_id, ranking_en_tienda, title;

# Ejercicio 43
#

WITH ingresos_diarios AS (
	SELECT
    YEAR(payment_date) AS anio,
    MONTH(payment_date) AS mes,
    DATE(payment_date) AS dia,
    SUM(amount) AS ingresos_dia
	FROM payment
	GROUP BY YEAR(payment_date), MONTH(payment_date), DATE(payment_date)
)

SELECT anio, mes,dia, ingresos_dia, SUM(ingresos_dia) OVER (
	PARTITION BY anio, mes
    ORDER BY dia
  ) AS ingresos_acumulados_mes
FROM ingresos_diarios
ORDER BY anio, mes, dia;

# Ejercicio 44
#

WITH alquileres_staff_dia AS (
	SELECT DATE(rental_date) AS dia, staff_id, COUNT(*) AS num_alquileres
	FROM rental
	GROUP BY DATE(rental_date), staff_id
)

SELECT a.dia, s.staff_id, CONCAT(s.first_name, ' ', s.last_name) AS empleado, a.num_alquileres,
	DENSE_RANK() OVER (
		PARTITION BY a.dia
		ORDER BY a.num_alquileres DESC
	) AS ranking_del_dia,
	LAG(a.num_alquileres) OVER (
		PARTITION BY a.staff_id
		ORDER BY a.dia
	) AS alquileres_dia_anterior, a.num_alquileres
    - LAG(a.num_alquileres) OVER (PARTITION BY a.staff_id ORDER BY a.dia)
    AS diferencia_vs_anterior
FROM alquileres_staff_dia a
JOIN staff s ON s.staff_id = a.staff_id
ORDER BY a.dia, ranking_del_dia, empleado;

# Ejercicio 45
#

WITH ingresos_diarios AS (
  SELECT
    YEAR(payment_date)  AS anio,
    MONTH(payment_date) AS mes,
    DATE(payment_date)  AS fecha,
    DAY(payment_date)   AS dia_mes,
    SUM(amount)         AS ingresos_dia
  FROM payment
  GROUP BY YEAR(payment_date), MONTH(payment_date), DATE(payment_date), DAY(payment_date)
),
acumulado_mes AS (
  SELECT
    anio, mes, fecha, dia_mes, ingresos_dia,
    SUM(ingresos_dia) OVER (
      PARTITION BY anio, mes
      ORDER BY fecha
    ) AS ingreso_acumulado
  FROM ingresos_diarios
)
SELECT
  dia_mes,
  AVG(ingreso_acumulado) AS media_acumulado_dia_mes,
  COUNT(DISTINCT CONCAT(anio, '-', LPAD(mes,2,'0'))) AS meses_con_dato
FROM acumulado_mes
GROUP BY dia_mes
ORDER BY dia_mes;

# Operaciones de negocio

# Ejercicio 46
#
# Ejercicio 47
#

