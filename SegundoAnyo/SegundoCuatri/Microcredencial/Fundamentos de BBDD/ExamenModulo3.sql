USE sakila;

## Ejercicio 1

# a

SELECT
	c.category_id,
	c.name AS categoria,
	COUNT(DISTINCT r.rental_id) AS num_alquileres,
	SUM(p.amount) AS ingresos_totales
FROM category c
JOIN film_category fc ON fc.category_id = c.category_id
JOIN inventory i ON i.film_id = fc.film_id
JOIN rental r ON r.inventory_id = i.inventory_id
JOIN payment p ON p.rental_id = r.rental_id
GROUP BY c.category_id, c.name
ORDER BY ingresos_totales DESC;

# b

SELECT
	c.category_id,
	c.name AS categoria,
	SUM(p.amount) AS ingresos_totales
FROM category c
JOIN film_category fc ON fc.category_id = c.category_id
JOIN inventory i ON i.film_id = fc.film_id
JOIN rental r ON r.inventory_id = i.inventory_id
JOIN payment p ON p.rental_id = r.rental_id
GROUP BY c.category_id, c.name
ORDER BY ingresos_totales DESC
LIMIT 3;

# c

SELECT
	c.category_id,
	c.name AS categoria,
	COUNT(DISTINCT r.rental_id) AS num_alquileres
FROM category c
JOIN film_category fc ON fc.category_id = c.category_id
JOIN inventory i ON i.film_id = fc.film_id
JOIN rental r ON r.inventory_id = i.inventory_id
GROUP BY c.category_id, c.name
ORDER BY num_alquileres DESC
LIMIT 3;

# d

# baratas

SELECT
  c.name AS categoria,
  ROUND(SUM(p.amount) / NULLIF(COUNT(DISTINCT r.rental_id), 0), 2) AS precio_medio_alquiler
FROM category c
JOIN film_category fc ON fc.category_id = c.category_id
JOIN inventory i      ON i.film_id      = fc.film_id
JOIN rental r         ON r.inventory_id = i.inventory_id
JOIN payment p        ON p.rental_id    = r.rental_id
GROUP BY c.category_id, c.name
ORDER BY precio_medio_alquiler ASC;

# caras

SELECT
  c.name AS categoria,
  ROUND(SUM(p.amount) / NULLIF(COUNT(DISTINCT r.rental_id), 0), 2) AS precio_medio_alquiler
FROM category c
JOIN film_category fc ON fc.category_id = c.category_id
JOIN inventory i      ON i.film_id      = fc.film_id
JOIN rental r         ON r.inventory_id = i.inventory_id
JOIN payment p        ON p.rental_id    = r.rental_id
GROUP BY c.category_id, c.name
ORDER BY precio_medio_alquiler DESC;

## Ejercicio 2

# a

SELECT
	c.customer_id,
	CONCAT(c.first_name, ' ', c.last_name) AS cliente,
	c.email,
	COUNT(r.rental_id) AS num_alquileres
FROM customer c
JOIN rental r ON r.customer_id = c.customer_id
GROUP BY c.customer_id, c.first_name, c.last_name, c.email
HAVING COUNT(r.rental_id) > 30
ORDER BY num_alquileres DESC;

# b 

WITH clientes_frecuentes AS (
	SELECT
		c.customer_id,
		CONCAT(c.first_name, ' ', c.last_name) AS cliente,
		c.email,
		COUNT(r.rental_id) AS num_alquileres
	FROM customer c
	JOIN rental r ON r.customer_id = c.customer_id
	GROUP BY c.customer_id, c.first_name, c.last_name, c.email
	HAVING COUNT(r.rental_id) > 30
),
alquileres_por_genero AS (
	SELECT
		cf.customer_id,
		cat.name AS genero,
		COUNT(*) AS alquileres_genero
	FROM clientes_frecuentes cf
	JOIN rental r ON r.customer_id = cf.customer_id
	JOIN inventory i ON i.inventory_id = r.inventory_id
	JOIN film_category fc ON fc.film_id = i.film_id
	JOIN category cat ON cat.category_id = fc.category_id
	GROUP BY cf.customer_id, cat.category_id, cat.name
),
datos_rankeados AS (
	SELECT
		apg.*,
		DENSE_RANK() OVER (
			PARTITION BY customer_id
			ORDER BY alquileres_genero DESC
		) AS rk
	FROM alquileres_por_genero apg
)
SELECT
	cf.customer_id,
	cf.cliente,
	cf.email,
	cf.num_alquileres,
	GROUP_CONCAT(dr.genero ORDER BY dr.genero SEPARATOR ', ') AS generos_preferidos,
	MAX(dr.alquileres_genero) AS alquileres_en_genero_top
FROM clientes_frecuentes cf
JOIN datos_rankeados dr ON dr.customer_id = cf.customer_id AND dr.rk = 1
GROUP BY cf.customer_id, cf.cliente, cf.email, cf.num_alquileres
ORDER BY cf.num_alquileres DESC;

## Ejercicio 3

# a

WITH tienda AS (
	SELECT
		i.store_id,
		f.film_id,
		f.title,
		COUNT(*) AS num_alquileres
	FROM rental r
	JOIN inventory i ON i.inventory_id = r.inventory_id
	JOIN film f ON f.film_id = i.film_id
	GROUP BY i.store_id, f.film_id, f.title
),
ranked AS (
	SELECT
		store_id, film_id, title, num_alquileres,
		DENSE_RANK() OVER (
			PARTITION BY store_id
			ORDER BY num_alquileres DESC
		) AS rk
	FROM tienda
)
SELECT
	store_id, 
    rk AS ranking_en_tienda, 
    film_id, title, 
    num_alquileres
FROM ranked
WHERE rk <= 10
ORDER BY store_id, rk, title;

# b

USE sakila;

WITH tienda AS (
	SELECT
		i.store_id,
		f.film_id,
		f.title,
		COUNT(*) AS num_alquileres
	FROM rental r
	JOIN inventory i ON i.inventory_id = r.inventory_id
	JOIN film f ON f.film_id = i.film_id
	GROUP BY i.store_id, f.film_id, f.title
),
stock AS (
	SELECT
		store_id,
		film_id,
		COUNT(*) AS copias_en_tienda
	FROM inventory
	GROUP BY store_id, film_id
),
ranked AS (
	SELECT
		t.store_id,
		t.film_id,
		t.title,
		t.num_alquileres,
		s.copias_en_tienda,
		DENSE_RANK() OVER (
			PARTITION BY t.store_id
			ORDER BY t.num_alquileres DESC
		) AS rk
	FROM tienda t
	JOIN stock s 
    ON s.store_id = t.store_id AND s.film_id = t.film_id
)
SELECT
	store_id,
	rk AS ranking_popularidad,
	film_id,
	title,
	num_alquileres,
	copias_en_tienda,
	ROUND(num_alquileres / NULLIF(copias_en_tienda, 0), 2) 
         AS alquileres_por_copia
FROM ranked
WHERE rk <= 10 AND copias_en_tienda <= 4
ORDER BY store_id, num_alquileres DESC, title;
