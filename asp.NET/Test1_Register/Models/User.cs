using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Test1_Register.Models
{
    public class User
    {
        public string username { get; set; }
        public string password { get; set; }
        public string sex { get; set; }
        public string province { get; set; }
        public string region { get; set; }
        public string email { get; set; }
        public string mobile { get; set; }
        public string major { get; set; }
        public string hobbies { get; set; }
        public string photo { get; set; }
        public string birthYM { get; set; }
        public string remark { get; set; }
    }
}