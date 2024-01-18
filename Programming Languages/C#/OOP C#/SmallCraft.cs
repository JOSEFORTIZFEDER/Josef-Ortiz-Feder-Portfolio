using System;

public class SmallCraft : IUFO
{
	public SmallCraft()
	{
	}

	public void fly()
	{
		Console.WriteLine("SmallCraft is flying");
	}
	public void goToHyperspace()
	{
        Console.WriteLine("SmallCraft is going to hyperspace");

    }
    public void land()
	{
        Console.WriteLine("SmallCraft is landing");

    }
}
