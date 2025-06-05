// Creating the objects
const person  = {
    firstName: "John",
    lastName: "Doe",
    age: 30
}
//Accessing the object 
console.log("Accessed the object named person: ",person.firstName);

// Using the this keyword
function Person (name, addr, age) {
    this.Name = name;
    this.Address = addr;
    this.Age = age;
    console.log(" Name:", this.Name,"\n","Address:", this.Address,"\n","Age:", this.Age)
}

// Creating the new object 
const Stud = new Person("Ram Mahat", "Sarlahi", 21);


console.log("\n");
// Accessing arrays
console.log("=========Arrays=========\n");

const arr1= [1,2,3,5];
console.log("The arr1:",arr1)
console.log("The arr1 with index 2 is",arr1[2])

console.log("--- Array Methods ---");
const cars = ["BMW", "Volvo", "Saab", "Ford"];

myString = cars.toString();
joining = cars.join("+");
pushing = cars.push("Honda");
shifted = cars.shift();

console.log("toString method: ",myString);
console.log("join method: ",joining);
console.log("pushed element Honda into the array", cars);
console.log("popped element Honda from the array : ",cars.pop(), cars);
console.log("The shifted array after removal of 1st element looks like", shifted);
unshifted = cars.unshift("Toyota");
console.log("The unshifted array after adding the Toyota at front looks like", cars);


console.log("\n");
console.log("========= Built in Objects =========\n");
console.log("1. Math Objects:");

console.log("Abs of -33.33 is: ", Math.abs(-33.33));
console.log("Round of -33.33 is: ", Math.round(-33.33));
console.log("Power of 2 and 3 is: ", Math.pow(2,3));
console.log("Square root of 9 is: ", Math.sqrt(9));
console.log("Random Number generated is: ", Math.random());

console.log("\n2. Date Objects: ");
var d= new Date();
var da= new Date(2018, 11, 24, 10, 33, 30);
var md = new Date("October 19, 2014 11:13:00");

console.log(d);
console.log(da);
console.log(md);


console.log("To return the day of month", d.getDate());
console.log("To return the day of week", d.getDay());
console.log("To return the year", d.getFullYear());
console.log("To return the hour", d.getHours());


console.log("\n3. String Objects: ");
console.log("Character at index 2 of Apple is: ", "Apple".charAt(2));
console.log("ASCII code at index 2 of Apple is: ", "Apple".charCodeAt(2));
console.log("Concatenating Apple and Cider: ", "Apple ".concat("Cider"));
console.log("Converting Apple to uppercase: ", "Apple ".toUpperCase());
console.log("Converting APPLE to lowercase: ", "Apple ".toLowerCase());
console.log("Slice in action at index 2 for Apple: ", "Apple ".slice(2));
console.log("Split per space for Apple Pie: ", "Apple Pie".split(" "));



console.log("\n");
console.log("========= RegEx =========\n");

let text = "Hello World!";
let pattern = /world/i;
console.log(pattern.test(text));


let x = {
    'name': "john",
    'age': 69
};

console.log(x['name']);