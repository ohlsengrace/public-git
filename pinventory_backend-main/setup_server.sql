

CREATE TABLE books(
asset_tag VARCHAR(19) PRIMARY KEY,
isbn VARCHAR(13) NOT NULL,
year VARCHAR(2) NOT NULL,
book_id VARCHAR(4) NOT NULL,
student_number VARCHAR(5)
);

CREATE TABLE textbook_sets(
isbn VARCHAR(13) PRIMARY KEY,
title VARCHAR,
department VARCHAR
);

CREATE TABLE students(
schoolid VARCHAR(2) NOT NULL,
student_number VARCHAR(5) PRIMARY KEY,
first_name VARCHAR(60) NOT NULL,
last_name VARCHAR(60) NOT NULL,
grade_level VARCHAR(3),
email VARCHAR(100)
);



