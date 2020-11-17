using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bridge
{
    class FaturaKopru:FaturaYonetimAbstraction
    {
        public override void FaturaOde(Faturatip tip)
        {
            FaturaOdemeImplementor.Ode(tip);
        }
    }
}
