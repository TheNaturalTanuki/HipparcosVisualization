using UnityEngine;
using Unity.Entities;
using Unity.Transforms;
using Unity.Rendering;
using Unity.Mathematics;
using System.IO;
using Newtonsoft.Json;
using System.Collections;

namespace hipparcos
{
   public class HipparcosJsonReader : MonoBehaviour
   {
      [SerializeField] private Mesh starMesh;
      [SerializeField] private Material starMaterial_1_O5V;
      [SerializeField] private Material starMaterial_2_B0V;
      [SerializeField] private Material starMaterial_3_A0V;
      [SerializeField] private Material starMaterial_4_F0V;
      [SerializeField] private Material starMaterial_5_G0V;
      [SerializeField] private Material starMaterial_6_K0V;
      [SerializeField] private Material starMaterial_7_M0V;

      // public GameObject starPrefab;
      // private Entity starEntityPrefab;
      private EntityManager entityManager;
      private EntityArchetype starArchetype;

      // private BlobAssetStore blobAssetStore;

      void Awake()
      {
         string path = "Assets/Resources/Hipparcos.json";
         // string path = "Assets/Resources/HipparcosMock.json";

         //Read the text from directly from the test.txt file
         StreamReader reader = new StreamReader(path);
         string jsonData = reader.ReadToEnd();

         Catalogue catalogue = JsonConvert.DeserializeObject<Catalogue>(jsonData);

         Debug.Log(catalogue.Stars[10].Hip);

         reader.Close();

         entityManager = World.DefaultGameObjectInjectionWorld.EntityManager;
         starArchetype = entityManager.CreateArchetype(
            typeof(Translation),
            typeof(RenderMesh),
            typeof(RenderBounds),
            typeof(LocalToWorld)
            );

         // blobAssetStore = new BlobAssetStore();
         // GameObjectConversionSettings settings = (GameObjectConversionSettings.FromWorld(World.DefaultGameObjectInjectionWorld, blobAssetStore));
         // starEntityPrefab = GameObjectConversionUtility.ConvertGameObjectHierarchy(starPrefab, settings);

         StartCoroutine(InitializeStars(catalogue));
      }

      // Update is called once per frame
      void Update()
      {

      }

      private IEnumerator InitializeStars(Catalogue catalogue)
      {
         foreach (Star star in catalogue.Stars)
         {
            SpawnStar(star);
         }
         yield return null;
      }

      void SpawnStar(Star star)
      {
         Material starMaterial;

         if      (star.Bv < -0.30) { starMaterial = starMaterial_1_O5V; }
         else if (star.Bv < -0.02) { starMaterial = starMaterial_2_B0V; }
         else if (star.Bv <  0.30) { starMaterial = starMaterial_3_A0V; }
         else if (star.Bv <  0.58) { starMaterial = starMaterial_4_F0V; }
         else if (star.Bv <  0.81) { starMaterial = starMaterial_5_G0V; }
         else if (star.Bv <  1.40) { starMaterial = starMaterial_6_K0V; }
         else                      { starMaterial = starMaterial_7_M0V; }


         Entity newStarEntity = entityManager.CreateEntity(starArchetype);
         entityManager.SetComponentData(newStarEntity, new Translation { Value = new float3(star.Xly, star.Yly, star.Zly) });
         entityManager.SetSharedComponentData(newStarEntity, new RenderMesh { mesh = starMesh, material = starMaterial });
      }
   }
}
