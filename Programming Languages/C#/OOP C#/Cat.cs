using System;

public class Cat : Animal
{
	public Cat()
	{
	}
    public override void move()
    {
        Console.WriteLine("A cat is moving");
    }
    public override void sleep()
    {
        Console.WriteLine("A cat is sleeping");
    }

    public override void eat()
    {
        Console.WriteLine("A cat is eating");
    }
    public void sing()
    {
        Console.WriteLine("An cat is singing");
    }
    public void wash()
    {
        Console.WriteLine("An cat is washing");
    }
    public void turnAround()
    {
        Console.WriteLine("An cat is turning around");
    }
}
