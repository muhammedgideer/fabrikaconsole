using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bridge
{
    class ElektrikFaturasiOde:FaturaOdemeImplementor
    {
        public override void Ode(Faturatip tip)
        {
            Console.WriteLine("Elektrik faturasi odendi");
        }
    }
}
