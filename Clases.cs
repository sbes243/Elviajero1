using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using UnityEditor;
using UnityEngine;
using System.Collections;

namespace Assets.scripts
{
    class Ciudad
    {
        public int name;
        public (int, int) pos;
        public Ciudad((int,int) pos)
        {
            this.pos = pos;
        }
    }
    class Mundo
    { 
        public List<List<Ciudad>> ciudades = new List<List<Ciudad>>();
        public int minx= int.MaxValue, miny=int.MaxValue, maxx=int.MinValue, maxy=int.MinValue;
        public Mundo()
        {

            ReadString();
            
            
            
            //var rand = new Random();
            //while (numciudades!=0)
            //{
            //    (int, int) pos = (rand.Next(0, n), rand.Next(0, n));
            //    if (!cityExist(pos))
            //    {
            //        insertarCiudad(new Ciudad(pos));
            //        numciudades--;
            //    }
                    
            //}
        }
        void ReadString()
        {
            string path = "D:/UCSP/semestre 7/ia/grupal/Alg_genetico/showing.txt";
            StreamReader reader = new StreamReader(path);
            string linea;
            while (!reader.EndOfStream)
            {
                linea=reader.ReadLine();
                string data=linea.Split('-')[1];
                List<string> puntos = data.Split('_').ToList();
                List<Ciudad> ciu = new List<Ciudad>();
                foreach(string cord in puntos)
                {
                    if (cord != null)
                    {
                        List<string> c = cord.Split(',').ToList();
                        if (c.Count==2)
                        {
                            int nx = int.Parse(c[0]);
                            int ny = int.Parse(c[1]);
                            minx = (nx < minx) ? nx : minx;
                            miny = (ny < miny) ? ny : miny;
                            maxx = (nx > maxx) ? nx : maxx;
                            maxy = (ny > maxy) ? ny : maxy;
                            ciu.Add(new Ciudad((nx, ny)));
                            
                        }
                    }
                }
                ciudades.Add(ciu);
            }
            reader.Close();
        }
    }

    
}
