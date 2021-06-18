using Console
include "hello2.g"

Main(string("Hello, world!", "Goodbye, world!") message): none {
    message += "h" + "hh"
    Console.writeLine(message)
}