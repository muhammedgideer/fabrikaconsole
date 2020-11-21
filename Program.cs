using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace fabrikaconsole
{
        public interface IArac
        {
            void BilgiGoster();
        }

        public class Araba : IArac
        {
            public void BilgiGoster()
            {
                Console.WriteLine("Araba Üretildi.");
            }
        }

        public class Tir : IArac
        {
            public void BilgiGoster()
            {
                Console.WriteLine("Tır Üretildi.");
            }
        }

        public class Motor : IArac
        {
            public void BilgiGoster()
            {
                Console.WriteLine("Motor Üretildi");
            }
        }
        public enum AracTipi
        {
            Araba = 1,
            Tir = 2,
            Motor = 3
        }

        public interface IAracFabrikasi
        {
            IArac AracUret(AracTipi tip);
        }

        public class AracFabrikasi : IAracFabrikasi
        {
            public IArac AracUret(AracTipi tip)
            {
                IArac Arac = null;
                switch (tip)
                {
                    case AracTipi.Araba:
                        Arac = new Araba();
                        break;
                    case AracTipi.Tir:
                        Arac = new Tir();
                        break;
                    case AracTipi.Motor:
                        Arac = new Motor();
                        break;
                }
                return Arac;
            }
        }


    class Program
    {

        static void Main(string[] args)
        {

            var AracFabrikasi = new AracFabrikasi();

            IArac aracAraba = AracFabrikasi.AracUret(AracTipi.Araba);
            aracAraba.BilgiGoster();

            IArac aracMotor = AracFabrikasi.AracUret(AracTipi.Motor);
            aracMotor.BilgiGoster();
            Console.Read();

        }


  
        }
    }

