using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Test3_Movie.Models
{
    public class SearchInput
    {
        public string genre { get; set; }
        public string title { get; set; }
        public int released { get; set; }
        public decimal minPrice { get; set; }
        public decimal maxPrice { get; set; }
        public bool includeMin { get; set; }
        public bool includeMax { get; set; }
        public bool validMin { get; set; }
        public bool validMax { get; set; }

        public SearchInput()
        {
            genre = "all";
            title = "";
            released = SearchUtil.ALL;
            includeMin = true;
            includeMax = true;
            minPrice = 0;
            maxPrice = 0;
            validMin = false;
            validMax = false;
        }
    }
}