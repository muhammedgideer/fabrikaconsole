using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bridge
{
    public class SuFaturasiOde:FaturaOdemeImplementor
    {
        public override void Ode(Faturatip tip)
        {
            Console.WriteLine("Su faturasi odendi");
        }
    }
}
