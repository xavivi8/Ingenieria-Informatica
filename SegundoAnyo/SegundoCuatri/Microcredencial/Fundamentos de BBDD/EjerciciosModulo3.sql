USE sakila;

## Ejercicios basicos

# Ejercicio 1
#  nom y apell de cada actor en una unica tabla actor

SELECT first_name, last_name FROM actor;

# Ejercicio 2

SELECT UPPER(CONCAT(first_name, ' ', last_name)) AS `Actor Name` FROM actor;

# Ejercicio 3

SELECT * FROM payment LIMIT 20;

# Ejercicio 4 

SELECT actor_id, first_name, last_name FROM actor WHERE first_name = 'Joe';

# Ejercicio 5

SELECT DISTINCT last_name FROM actor;

# Ejercicio 6

SELECT title, description, length, rating FROM film WHERE length > 180;

# Ejercicio 7

SELECT * FROM customer WHERE active = 0 OR last_name LIKE '%M';

# Ejercicio 8



