using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bridge
{
    class Program
    {
        static void Main(string[] args)
        {
            FaturaYonetimAbstraction faturaYonetim =new FaturaKopru();
            faturaYonetim.FaturaOdemeImplementor = new SuFaturasiOde();
            faturaYonetim.FaturaOde(new Faturatip { Title = "Su Faturasi Bildirimi" });
            faturaYonetim.FaturaOdemeImplementor = new ElektrikFaturasiOde();
            faturaYonetim.FaturaOde(new Faturatip { Title = "Su Faturasi Bildirimi" });

            Console.ReadLine();
        }
    }
}
