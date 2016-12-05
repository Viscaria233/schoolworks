using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Test3_Movie.Models
{
    public class SearchUtil
    {
        public const int ALL = 0;
        public const int RELEASED = 1;
        public const int UNRELEASED = -1;

        public SearchInput input { get; set; }

        public List<int> search(MovieDbContext db, List<int> ids)
        {
            var list = from m in db.Movies
                       select m;
            if (ids != null)
            {
                list = from m in list
                       where ids.Contains(m.ID)
                       select m;
            }
            if (input.genre != "all")
            {
                list = from m in list
                       where m.Genre == input.genre
                       select m;
            }
            if (input.title != "")
            {
                list = from m in list
                       where m.Title.Contains(input.title)
                       select m;
            }
            if (input.released != ALL)
            {
                list = from m in list
                       where DateTime.Now.CompareTo(m.ReleaseDate) * input.released > 0
                       select m;
            }
            if (input.validMin)
            {
                if (input.includeMin)
                {
                    list = from m in list
                           where m.Price >= input.minPrice
                           select m;
                }
                else
                {
                    list = from m in list
                           where m.Price > input.minPrice
                           select m;
                }
            }
            if (input.validMax)
            {
                if (input.includeMax)
                {
                    list = from m in list
                           where m.Price <= input.maxPrice
                           select m;
                }
                else
                {
                    list = from m in list
                           where m.Price < input.maxPrice
                           select m;
                }
            }

            var result = from m in list
                         select m.ID;
            return result.ToList();
        }
    }
}