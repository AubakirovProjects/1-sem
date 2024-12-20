CREATE DATABASE product_inventory;

CREATE TABLE categories (
    id SERIAL PRIMARY KEY,
    category_name VARCHAR(255) NOT NULL
);

CREATE TABLE products (
    id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    price NUMERIC(10, 2) NOT NULL,
    quantity INT NOT NULL,
    category_id INT REFERENCES categories(id) ON DELETE SET NULL
);

CREATE TABLE sales (
    id SERIAL PRIMARY KEY,
    product_id INT REFERENCES products(id) ON DELETE CASCADE,
    sale_date DATE NOT NULL,
    quantity_sold INT NOT NULL
);

INSERT INTO categories (category_name)
VALUES 
('Овощи'),
('Фрукты'),
('Молочные продукты');

INSERT INTO products (name, price, quantity, category_id)
VALUES
('Морковь', 50.00, 100, 1),
('Помидор', 65.00, 80, 1),
('Яблоко', 70.00, 150, 2),
('Персик', 3.00, 40, 2),
('Молоко', 90.00, 50, 3),
('Йогурт', 120.00, 75, 3);

INSERT INTO sales (product_id, sale_date, quantity_sold)
VALUES
(1, '2024-12-01', 20),
(2, '2024-12-02', 30),
(3, '2024-12-03', 10),
(4, '2024-12-04', 25),
(5, '2024-12-05', 40),
(6, '2024-12-06', 15);

SELECT p.id, p.name, p.price, p.quantity, c.category_name
FROM products p
JOIN categories c ON p.category_id = c.id
WHERE c.category_name = 'Фрукты';

SELECT id, name, price, quantity
FROM products
WHERE quantity < 50;

SELECT SUM(p.price * s.quantity_sold) AS total_sales
FROM sales s
JOIN products p ON s.product_id = p.id
WHERE s.sale_date BETWEEN '2024-12-01' AND '2024-12-05';

UPDATE products
SET quantity = quantity - (
    SELECT quantity_sold
    FROM sales
    WHERE sales.product_id = products.id
    LIMIT 1
)
WHERE id = 1; 

SELECT p.name, c.category_name, SUM(s.quantity_sold) AS total_sold
FROM sales s
JOIN products p ON s.product_id = p.id
JOIN categories c ON p.category_id = c.id
GROUP BY p.id, c.category_name
ORDER BY total_sold DESC;

UPDATE products
SET price = price * 1.10
WHERE category_id = (SELECT id FROM categories WHERE category_name = 'Овощи');

DELETE FROM products
WHERE id = 2;