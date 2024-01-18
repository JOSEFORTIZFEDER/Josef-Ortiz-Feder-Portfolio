// See https://aka.ms/new-console-template for more information
public class Problem1
{
    public static IEnumerable<int> myFilter(IEnumerable<int> input)
    {
        IEnumerable<int> filtered = input.Where(input => input <= 50 || input %5!=0);
        filtered = filtered.Select(filtered => filtered * filtered * filtered);
        filtered = filtered.Where(filtered => filtered % 2 != 0);
        return filtered;
    }

    static void Main(string[] args)
    {
        Random rnd = new Random(5); // Important to seed with 5 for repeatability.
        var listForProblem =
          Enumerable.Range(1, 100).Select(i => rnd.Next() % 101);
        var answer = Problem1.myFilter(listForProblem);
        foreach (int i in answer)
        {
            Console.WriteLine(i);
        }
    }
}
