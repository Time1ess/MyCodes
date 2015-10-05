drop database if exists java;
create database java;
use java;
drop table if exists tbl_user;
create table tbl_user(id int(20) primary key auto_increment, name varchar(20), pwd varchar(20));
select * from tbl_user;