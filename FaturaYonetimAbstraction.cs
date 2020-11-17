using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bridge
{
    abstract class FaturaYonetimAbstraction
    {
        public FaturaOdemeImplementor FaturaOdemeImplementor { get; set; }
        public abstract void FaturaOde(Faturatip tip);
    }
}
