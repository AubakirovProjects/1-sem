CREATE DATABASE products_new;

CREATE TABLE categories_new (
    id SERIAL PRIMARY KEY,
    category_name VARCHAR(255) UNIQUE NOT NULL
);

CREATE TABLE products_new (
    id SERIAL PRIMARY KEY,
    name VARCHAR(255) UNIQUE NOT NULL,
    price NUMERIC(10, 2) NOT NULL,
    quantity INT NOT NULL,
    category_id INT NOT NULL REFERENCES categories_new(id) ON DELETE CASCADE
);

CREATE TABLE sale_new (
    id SERIAL PRIMARY KEY,
    product_id INT NOT NULL REFERENCES products_new(id) ON DELETE CASCADE,
    sale_date DATE NOT NULL,
    quantity_sold INT NOT NULL
);

CREATE INDEX idx_category_name ON categories_new(category_name);
CREATE INDEX idx_product_name ON products_new(name);
CREATE INDEX idx_sale_date ON sales_new(sale_date);
