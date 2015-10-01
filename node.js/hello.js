'use strict';

var s="Hello";

function greet(name){
	console.log(s+', '+name+'!');
}

function hello(){
	console.log('Hello world.');
}

module.exports={
	greet:greet,
	hello:hello
}
