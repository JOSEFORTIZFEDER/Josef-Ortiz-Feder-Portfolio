using System;

public class LargeCraft : IUFO
{
	public LargeCraft()
	{
	}
    public void fly()
    {
        Console.WriteLine("LargeCraft is flying");
    }
    public void goToHyperspace()
    {
        Console.WriteLine("LargeCraft is going to hyperspace");

    }
    public void land()
    {
        Console.WriteLine("LargeCraft is landing");

    }
}
