using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml.Linq;

namespace thuumDictionary
{
    public partial class mainForm : Form
    {
        public mainForm()
        {
            InitializeComponent(); 
            // set cbbbox autocomplete modes
            entryCbox.AutoCompleteMode = AutoCompleteMode.SuggestAppend;
            entryCbox.AutoCompleteSource = AutoCompleteSource.CustomSource;
            // set first radio button to checked 
            engToDragRadio.Checked = true;
        }

        // add helper attribs
        private Point mouseOffset;
        private bool isMouseDown = false;
        StringCollection wordsCollection = new StringCollection();
        StringCollection types = new StringCollection();
        StringCollection translations = new StringCollection();
        StringCollection canon = new StringCollection();
        StringCollection notes = new StringCollection();
        private string namespaceName = "thuumDictionary";

// //////////////////////////////////////////////////////////////////////////
//      XML data handlers and loaders
        public static XDocument GetDocument(string docName)
        {
            using (Stream resourceStream = Assembly.GetExecutingAssembly()
                                                   .GetManifestResourceStream(docName))
            {
                using (StreamReader resourceStreamReader = new StreamReader(resourceStream))
                {
                    String xml = resourceStreamReader.ReadToEnd();
                    XDocument doc = XDocument.Parse(xml);
                    return doc;
                }
            }
        }

        public void GetEnglishDragonDoc(ref StringCollection words, ref StringCollection types, ref StringCollection translations)
        {
            string docName = namespaceName + ".english_dragon.xml";
            XDocument doc = GetDocument(docName);
            var collection = doc.Element("dictionary").Elements("word").Select
            (x => new
            {
                engWord = (string)x.Element("English_Word"),
                type = (string)x.Element("Word_Type"),
                translation = (string)x.Element("Dragon_Translation")
            }
            );
            foreach (var item in collection)
            {
                words.Add(item.engWord);
                types.Add(item.type);
                translations.Add(item.translation);
            }
        }

        public void GetDragonEnglishDoc(ref StringCollection words, ref StringCollection types, ref StringCollection canon, ref StringCollection translations, ref StringCollection notes)
        {
            string docName = namespaceName + ".dragon_english.xml";
            XDocument doc = GetDocument(docName);
            var collection = doc.Element("dictionary").Elements("word").Select
            (x => new
            {
                dragWord = (string)x.Element("Dragon_Word"),
                type = (string)x.Element("Word_Type"),
                canon = (string)x.Element("Canon_Level"),
                translation = (string)x.Element("Definition"),
                note = (string)x.Element("Notes")
            }
            );
            foreach (var item in collection)
            {
                words.Add(item.dragWord);
                types.Add(item.type);
                notes.Add(item.note);
                translations.Add(item.translation);
                canon.Add(item.canon);
            }
        }
// ////////////////////////////////////////////////////////////////////////
//      Radio Button handlers
        private void dragToEngRadio_CheckedChanged(object sender, EventArgs e)
        {
            wordsCollection.Clear();
            types.Clear();
            translations.Clear();
            canon.Clear();
            notes.Clear();

            GetDragonEnglishDoc(ref wordsCollection, ref types, ref canon, ref translations, ref notes);

            // create and populate autocomplete list
            AutoCompleteStringCollection autoCompCol = new AutoCompleteStringCollection();
            foreach (string word in wordsCollection)
            {
                autoCompCol.Add(word);
            }
            //set autocomplete list
            entryCbox.AutoCompleteCustomSource = autoCompCol;
        }

        private void engToDragRadio_CheckedChanged(object sender, EventArgs e)
        {
            wordsCollection.Clear();
            types.Clear();
            translations.Clear();

            // populate lists
            GetEnglishDragonDoc(ref wordsCollection, ref types, ref translations);

            // create and populate autocomplete list
            AutoCompleteStringCollection autoCompCol = new AutoCompleteStringCollection();
            foreach (string word in wordsCollection)
            {
                autoCompCol.Add(word);
            }
            //set autocomplete list
            entryCbox.AutoCompleteCustomSource = autoCompCol;

        }
// ////////////////////////////////////////////////////////////////////////
//      Timer handlers. Updates labels
        private void eventTimer_Tick(object sender, EventArgs e)
        {
            string targetString = entryCbox.Text;
            if (!string.IsNullOrEmpty(targetString))
            {
                targetString = char.ToUpper(targetString[0]) + targetString.Substring(1);
            }
            int index = wordsCollection.IndexOf(targetString);
            if (index != -1)
            {
                tranLabel.Text = translations[index];
                typeLabel.Text = types[index];
                if (dragToEngRadio.Checked)
                {
                    canonLabel.Text = canon[index];
                    notesLabel.Text = notes[index];
                }
                else
                {
                    canonLabel.Text = " ";
                    notesLabel.Text = " ";
                }
            }
            else
            {
                tranLabel.Text = targetString;
                typeLabel.Text = " ";
                notesLabel.Text = " ";
                canonLabel.Text = " ";
            }
        }

        private void mainForm_MouseDown(object sender, MouseEventArgs e)
        {
            int xOffset;
            int yOffset;

            if (e.Button == MouseButtons.Left)
            {
                xOffset = -e.X;
                yOffset = -e.Y;
                mouseOffset = new Point(xOffset, yOffset);
                isMouseDown = true;
            }

        }

        private void mainForm_MouseMove(object sender, MouseEventArgs e)
        {
            if (isMouseDown)
            {
                Point mousePos = Control.MousePosition;
                mousePos.Offset(mouseOffset.X, mouseOffset.Y);
                Location = mousePos;
            }

        }

        private void mainForm_MouseUp(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                isMouseDown = false;
            }

        }

        private void closeButtonPicbox_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void minButtonPicbox_Click(object sender, EventArgs e)
        {
            this.WindowState = FormWindowState.Minimized;
        }

        private void closeButtonPicbox_MouseEnter(object sender, EventArgs e)
        {
            System.Reflection.Assembly myAssembly = System.Reflection.Assembly.GetExecutingAssembly();
            Stream myStream = myAssembly.GetManifestResourceStream(namespaceName + ".button_max_glow.png");
            Image maxButtonGlow = Image.FromStream(myStream);

            closeButtonPicbox.Image = maxButtonGlow;

        }

        private void closeButtonPicbox_MouseLeave(object sender, EventArgs e)
        {
            System.Reflection.Assembly myAssembly = System.Reflection.Assembly.GetExecutingAssembly();
            Stream myStream = myAssembly.GetManifestResourceStream(namespaceName + ".button_max_noglow.png");
            Image maxButtonNoGlow = Image.FromStream(myStream);

            closeButtonPicbox.Image = maxButtonNoGlow;

        }

        private void minButtonPicbox_MouseEnter(object sender, EventArgs e)
        {
            System.Reflection.Assembly myAssembly = System.Reflection.Assembly.GetExecutingAssembly();
            Stream myStream = myAssembly.GetManifestResourceStream(namespaceName + ".button_min_glow.png");
            Image maxButtonGlow = Image.FromStream(myStream);

            minButtonPicbox.Image = maxButtonGlow;

        }

        private void minButtonPicbox_MouseLeave(object sender, EventArgs e)
        {
            System.Reflection.Assembly myAssembly = System.Reflection.Assembly.GetExecutingAssembly();
            Stream myStream = myAssembly.GetManifestResourceStream(namespaceName + ".button_min_noglow.png");
            Image maxButtonNoGlow = Image.FromStream(myStream);

            minButtonPicbox.Image = maxButtonNoGlow;

        }

    }
}
