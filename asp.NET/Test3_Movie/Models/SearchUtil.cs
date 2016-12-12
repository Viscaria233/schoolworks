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

        public List<Movie> search(List<Movie> list)
        {
            var result = from m in list
                            select m;
            if (list != null)
            {
                result = result.Where(m => list.Contains(m));
            }
            if (input.genre != "all")
            {
                result = result.Where(m => m.Genre == input.genre);
            }
            if (input.title != "")
            {
                result = result.Where(m => m.Title.Contains(input.title));
            }
            if (input.released != ALL)
            {
                result = result.Where(m => DateTime.Now.CompareTo(m.ReleaseDate) * input.released > 0);
            }
            if (input.validMin)
            {
                if (input.includeMin)
                {
                    result = result.Where(m => m.Price >= input.minPrice);
                }
                else
                {
                    result = result.Where(m => m.Price > input.minPrice);
                }
            }
            if (input.validMax)
            {
                if (input.includeMax)
                {
                    result = result.Where(m => m.Price <= input.maxPrice);
                }
                else
                {
                    result = result.Where(m => m.Price < input.maxPrice);
                }
            }

            return result.ToList();
        }
    }
}