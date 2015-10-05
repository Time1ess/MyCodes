use java;
create table tbl_classroom(
	id int not null primary key auto_increment,
	build_id int not null,
	classroom_code varchar(10) not null
)default charset=utf8;
