using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace CSV_to_XML_parser
{
    class Program
    {
        static void Main(string[] args)
        {
            Program app = new Program();
            app.doStuff();

        }

        public void doStuff()
        {

            Console.Write("\nEnter root directory name: ");
            string directory = Console.ReadLine();

            Console.Write("\nEnter record element name: ");
            string rootElement = Console.ReadLine();

            string url = "http://samplecsvs.s3.amazonaws.com/Sacramentorealestatetransactions.csv";

            FileInfo file = new FileInfo("test.xml");
            FileInfo inFile = new FileInfo("thuum_dragon_english.csv");
            CsvXmlParser parser = new CsvXmlParser(directory, rootElement);

            //parser.SetSource(url);
            parser.SetSource(inFile);

            parser.WriteToFile(file.FullName);

        }
    }

}
