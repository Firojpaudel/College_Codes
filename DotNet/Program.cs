using System;

namespace DataTypes
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("=== C# Data Types Demonstration ===\n");

            // --- Integer Types ---
            Console.WriteLine("--- Integer Types ---");
            int age = 25;                      // 32-bit signed integer
            long population = 7800000000L;     // 64-bit signed integer
            Console.WriteLine($"Age (int): {age}");
            Console.WriteLine($"World Population (long): {population}\n");

            // --- Floating Point Types ---
            Console.WriteLine("--- Floating Point Types ---");
            float pi = 3.14f;                  // 32-bit float (single-precision)
            double gravity = 9.80665;          // 64-bit double (double-precision)
            decimal money = 199.99m;           // 128-bit decimal (high precision for currency)
            Console.WriteLine($"Pi (float): {pi}");
            Console.WriteLine($"Gravity (double): {gravity}");
            Console.WriteLine($"Price (decimal): ${money}\n");

            // --- Character Type ---
            Console.WriteLine("--- Character Type ---");
            char grade = 'A';                  // Single character
            Console.WriteLine($"Grade (char): {grade}\n");

            // --- Boolean Type ---
            Console.WriteLine("--- Boolean Type ---");
            bool isPassed = true;              // true/false
            Console.WriteLine($"Is Passed? (bool): {isPassed}\n");

            // --- String Type ---
            Console.WriteLine("--- String Type ---");
            string name = "Alice";             // Sequence of characters
            Console.WriteLine($"Name (string): {name}\n");

            // --- DateTime Type ---
            Console.WriteLine("--- DateTime Type ---");
            DateTime today = DateTime.Now;     // Current date and time
            Console.WriteLine($"Current Date & Time (DateTime): {today}\n");

            // --- Object Type ---
            Console.WriteLine("--- Object Type ---");
            object anything = "This can hold anything!";
            Console.WriteLine($"Object Example: {anything}\n");

            // End message
            Console.WriteLine("=== End of Data Types Demo ===");
            Console.WriteLine("\nPress any key to exit...");
            Console.ReadKey();
        }
    }
}