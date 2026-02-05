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

##





