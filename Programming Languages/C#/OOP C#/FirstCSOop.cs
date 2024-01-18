// See https://aka.ms/new-console-template for more information
using System;
using System.Globalization;

internal class FirstCSOop
{
    static void Main(String[] args)
    {
        Console.WriteLine("Problem 1: Animal Inheritance\nDog:");

        Dog dog = new Dog();
        dog.move();
        dog.sleep();
        dog.eat();
        dog.sing();
        dog.wash();
        dog.turnAround();
        Console.WriteLine("Cat:");
        Cat cat = new Cat();
        cat.move();
        cat.sleep();    
        cat.eat();
        cat.sing();
        cat.wash();
        cat.turnAround();
        Console.WriteLine("Bird:");

        Bird bird = new Bird();
        bird.move();
        bird.sleep();
        bird.eat();
        bird.sing();
        bird.wash();
        bird.turnAround();

        Console.WriteLine("\nProblem 2: UFO Interfaces\nSmallCraft:");
        SmallCraft smallCraft = new SmallCraft();
        smallCraft.fly();
        smallCraft.goToHyperspace();
        smallCraft.land();

        Console.WriteLine("LargeCraft:");

        LargeCraft largeCraft = new LargeCraft();
        largeCraft.fly();
        largeCraft.goToHyperspace();
        largeCraft.land();

        Console.WriteLine("BossCraft:");
        BossCraft bossCraft = new BossCraft();
        bossCraft.fly();
        bossCraft.goToHyperspace();
        bossCraft.land();




    }
}
