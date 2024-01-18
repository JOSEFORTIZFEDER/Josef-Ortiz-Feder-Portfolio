// See https://aka.ms/new-console-template for more information
public class Problem2

{

    public static IEnumerable<int> myFilter(IEnumerable<int> input)
    {
        input = input.Where(input => input >= 42 || input % 6 != 0);
        input = input.Select(input => input * input);
        input = input.Where(input => input % 2 == 0);
        return input;
    }
    static void Main(string[] args)

    {

        Random rnd = new Random();

        var listForProblem =

          Enumerable.Range(1, 100).Select(i => rnd.Next() % 101);

        var answer = Problem2.myFilter(listForProblem);

        foreach (int i in answer)

        {

            Console.WriteLine(i);

        }

    }

}