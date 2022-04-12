using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Assets.scripts;
public class Viajes : MonoBehaviour
{
    public GameObject ciudad,piso,camino;
    Mundo mundo;
    public int n=100;
    private void Awake()
    {
        mundo = new Mundo();

        int difx=(mundo.minx+mundo.maxx)/2, dify= (mundo.miny + mundo.maxy) / 2;
        int tam = (difx > dify) ? difx : dify;

        piso.transform.localScale = new Vector3(tam*2, piso.transform.localScale.y, tam*2);
        piso.transform.position = new Vector3(difx, -.25f, dify);
        Camera.main.transform.position = new Vector3(difx, 10.0f, dify);
        Camera.main.orthographicSize = tam;
    }
    // Start is called before the first frame update
    void Start()
    {
        foreach (Ciudad c in mundo.ciudades[0])
        {
            Instantiate(ciudad,new Vector3(c.pos.Item1,0,c.pos.Item2),new  Quaternion(0, 0, 0, 0));
        }
        StartCoroutine(drawCaminos());
    }
    IEnumerator drawCaminos()
    {
        foreach(List<Ciudad> c in mundo.ciudades)
        {
            GameObject[] caminos = GameObject.FindGameObjectsWithTag("Camino");
            foreach (GameObject g in caminos) //dudoso
            {
                Destroy(g);
            }
            for (int i = 0; i < c.Count - 1; i++)
            {
                
                GameObject a = Instantiate(camino);
                LineRenderer lr = a.GetComponent<LineRenderer>();
                List < Vector3 > posi = new List<Vector3>(){new Vector3(c[i].pos.Item1, 0, c[i ].pos.Item2),new Vector3(c[i + 1].pos.Item1, 0, c[i + 1].pos.Item2)};
                lr.SetPositions(posi.ToArray());

            }
            yield return new WaitForSeconds(2f);
        }
    }
    // Update is called once per frame
    void Update()
    {
       
    }
}
