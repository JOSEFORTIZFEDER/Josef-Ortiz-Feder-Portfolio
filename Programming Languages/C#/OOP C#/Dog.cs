using System;

public class Dog : Animal
{
	public Dog()
	{

	}
    public override void move()
    {
        Console.WriteLine("A dog is moving");
    }
    public override void sleep()
    {
        Console.WriteLine("A dog is sleeping");
    }
    
    public override void eat()
    {
        Console.WriteLine("A dog is eating");
    }
    public void sing()
    {
        Console.WriteLine("An dog is singing");
    }
    public void wash()
    {
        Console.WriteLine("An dog is washing");
    }
    public void turnAround()
    {
        Console.WriteLine("An dog is turning around");
    }
}
