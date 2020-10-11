using UnityEngine;
using System.IO;
using Newtonsoft.Json;

namespace hipparcos
{
   public class HipparcosJsonReader : MonoBehaviour
   {
      // Start is called before the first frame update
      void Start()
      {
         string path = "Assets/Resources/HipparcosMock.json";

         //Read the text from directly from the test.txt file
         StreamReader reader = new StreamReader(path);
         string jsonData = reader.ReadToEnd();

         Catalogue catalogue = JsonConvert.DeserializeObject<Catalogue>(jsonData);

         Debug.Log(catalogue.Stars[10].Hip);

         reader.Close();
      }

      // Update is called once per frame
      void Update()
      {

      }
   }
}
