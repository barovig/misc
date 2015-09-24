using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace CSV_to_XML_parser
{
    class CsvXmlParser
    {
        // attributes
        private string m_RootName;
        private string m_ElementName;
        private String[] attribs;
        private List<List<string>> recordsList = new List<List<string>>();

        // properties
        public string RootName
        {
            get { return m_RootName; }
            set { m_RootName = value; }
        }
        public string ElementName
        {
            get { return m_ElementName; }
            set { m_ElementName = value; }
        }

        // ctors
        public CsvXmlParser(string rootName, string elemName)
        {
            m_RootName = rootName;
            m_ElementName = elemName;
        }

        // public methods
        public void SetSource(string url)
        {
            ReadUrlData(url);
        }
        public void SetSource(FileInfo file)
        {
            ReadFileData(file);
        }
        public XDocument GetDocument()
        {
            XDocument xDoc = XDocument.Load(GetDocumentMemoryStream(), LoadOptions.None);            
            return xDoc;
        }
        public Stream GetDocumentMemoryStream()
        {
            Stream memStrm = new MemoryStream();        // DON'T close memStrm - it will be inaccessible

            StreamWriter sw = new StreamWriter(memStrm, Encoding.UTF8);     // DON'T CLOSE StreamWriter - it will close MemStrm

            sw.WriteLine("<?xml version=\"1.0\"?>");
            sw.WriteLine("<{0}>", RootName);

            foreach (List<string> record in recordsList)
            {
                sw.WriteLine("<{0}>", ElementName);

                int i = 0;
                foreach (string attrib in record)
                {
                    sw.WriteLine("<{0}>" + attrib + "</{0}>", attribs[i]);
                    i++;
                }

                sw.WriteLine("</{0}>", ElementName);
            }

            sw.WriteLine("</{0}>", RootName);
            
            sw.Flush(); // need to flush sw, dunno why
            memStrm.Position = 0;   // reset memStrm position
            return memStrm;
        }

        public void WriteToFile(string fileName)
        {
            using (FileStream fs = new FileStream(fileName, FileMode.Create))
            {
                using (Stream memStrm = GetDocumentMemoryStream())
                {
                    memStrm.Position = 0;
                    memStrm.CopyTo(fs);
                    fs.Close();
                }
            }
        }

        //private methods. 
        /////////////////////////////////////////////////
        // FACTOR OUT ReadData method. pass it a stream.
        // ie. create void ReadData(StreamReader sr) method
        private void ReadFileData(FileInfo file)
        {
            using (StreamReader sr = new StreamReader(file.FullName))
            {
                // reads first line and breaks it into attributes stored as str array.
                attribs = sr.ReadLine().Split(',');

                // remove quotes, non alphanums, convert whitespaces
                for (int i = 0; i < attribs.Length; i++)
                {
                    attribs[i] = RemoveNonAlphaNumChars(attribs[i]);
                    attribs[i] = attribs[i].Trim('\"').Replace(" ", "_");
                }
                string word = "";

                while (word != "-1")
                {
                    List<string> wordList = new List<string>();

                    for (int i = 0; i < attribs.Length; i++)
                    {
                        word = GetWord(sr);
                        wordList.Add(word);
                    }
                    recordsList.Add(wordList);
                }

                recordsList.RemoveAt(recordsList.Count - 1);    // remove last element. just a cleanup
            }
        }
        private void ReadUrlData(string url)
        {
            using (StreamReader sr = new StreamReader(GetStreamFromUrl(url)))
            {
                // reads first line and breaks it into attributes stored as str array.
                attribs = sr.ReadLine().Split(',');


                // remove quotes, non alphanums, convert whitespaces
                for (int i = 0; i < attribs.Length; i++)
                {
                    attribs[i] = RemoveNonAlphaNumChars(attribs[i]);
                    attribs[i] = attribs[i].Trim('\"').Replace(" ", "_");
                }
                string word = "";

                while (word != "-1")
                {
                    List<string> wordList = new List<string>();

                    for (int i = 0; i < attribs.Length; i++)
                    {
                        word = GetWord(sr);
                        wordList.Add(word);
                    }
                    recordsList.Add(wordList);
                }

                recordsList.RemoveAt(recordsList.Count - 1);    // remove last element. just a cleanup
            }
        }//////////////////////////////////////////////
        private Stream GetStreamFromUrl(string url)
        {
            // get resource as a string
            WebClient client = new WebClient();
            string reply = client.DownloadString(url);

            // create stream object and put string in it
            MemoryStream stream = new MemoryStream();
            StreamWriter writer = new StreamWriter(stream);

            writer.Write(reply);
            writer.Flush();
            stream.Position = 0;

            return stream;
        }
        private string RemoveNonAlphaNumChars(string aString)
        {
            // create LINQ query to remove non-alphanumeric chars
            IEnumerable<char> removeNonAlphaNum =
                from ch in aString
                where Char.IsLetterOrDigit(ch) || Char.IsWhiteSpace(ch) || ch == '_'
                select ch;

            // declare empty return string
            string processedStr = "";

            //Execute query
            foreach (char c in removeNonAlphaNum)
            {
                processedStr += c;
            }

            return processedStr;
        }

        /////////////////////////////////////////////////
        // REVIEW GetWord() method - it has errors. if not, error is in the ReadXData methods
        private string GetWord(StreamReader stream)
        {
            // create an empty word - this will be returned
            string word = "";

            // states whether we are inside double quotes block
            bool insideQuotes = false;

            // states whether a word from double quotes block has been extracted
            bool extractedWord = false;

            //empty character - will be appended to 'word'
            char c = 'a';

            while (c != ',' && !extractedWord)
            {

                // read char from stream and check if it is -1
                int n = stream.Read();

                if (n != -1)
                    c = Convert.ToChar(n);
                else
                    return "-1";

                // deal with rows terminated by CRLF, not comma <- wrong. rewrite
                if ((c == '\r' && stream.Peek() == '\n') && !insideQuotes)
                {
                    stream.Read();
                    return word;
                }

                if (c == '\"')
                {
                    insideQuotes = true;
                    do
                    {
                        // read next char, the quote we read before can be ignored
                        char c2 = Convert.ToChar(stream.Read());

                        if (c2 == '"' && insideQuotes)   // if next char is quote
                        {
                            int peekChar = stream.Peek();
                            char cPeekChar = (char)peekChar;

                            if (peekChar == '"')   // double doublequotes detected -> add quotes to word string
                            {
                                word += "&quot;";
                                stream.Read(); // move ahead 1 position, so that next quote can be ignored
                            }
                            else    // this is last quote pair -> return word
                            {
                                stream.Read();          // consume this quote first, otherwise it will be read on next getWord() iteration
                                if (stream.Peek() == '\n')  // if next char is newline, consume it as well
                                    stream.Read();
                                insideQuotes = false;   // we are not inside double quotes
                                extractedWord = true;   // we have extracted a word, can return a word 
                            }
                        }
                        else
                        {
                            word += ValidateChar(c2);
                        }
                    } while (insideQuotes);
                }

                if (c == '\n')  // deals with cases when we dont have additional notes (fifth word), puts empty word instead
                {
                    return word;
                }

                if (c != '"' && c != ',')    //prevent adding these two chars in outer while loop - dodgy, I know
                {
                    // REPLACE THIS BY ValidateChar(char c) : char FUNCTIOn
                    word += ValidateChar(c);
                    /////////////////////////////
                }
            }
            return word.Trim();
        }
        /////////////////////////////////////////////
        private string ValidateChar(char c)
        {
            string word = "";
            switch (c)
            {
                case '>':
                    word += "&gt;";
                    break;
                case '<':
                    word += "&lt;";
                    break;
                case '\'':
                    word += "&apos;";
                    break;
                case '&':
                    word += "&amp;";
                    break;
                default:
                    word += c;
                    break;
            }

            return word;
        }
    }
}
