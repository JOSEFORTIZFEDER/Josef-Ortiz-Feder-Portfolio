using System;

public class Bird : Animal
{
	public Bird()
	{
	}
    public override void move()
    {
        Console.WriteLine("A bird is moving");
    }
    public override void sleep()
    {
        Console.WriteLine("A bird is sleeping");
    }

    public override void eat()
    {
        Console.WriteLine("A bird is eating");
    }
    public void sing()
    {
        Console.WriteLine("An bird is singing");
    }
    public void wash()
    {
        Console.WriteLine("An bird is washing");
    }
    public void turnAround()
    {
        Console.WriteLine("An bird is turning around");
    }
}
