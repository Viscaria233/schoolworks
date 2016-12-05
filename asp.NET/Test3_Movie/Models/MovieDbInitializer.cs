using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Web;

namespace Test3_Movie.Models
{
    public class MovieDbInitializer : DropCreateDatabaseAlways<MovieDbContext>
    {
        protected override void Seed(MovieDbContext context)
        {
            string[] titles = { "你的名字", "AAA", "CCbbCCaC", "bBBaaab", "我的名字", "他的名字", "小学生开学啦" };
            int[] years = { 2016, 2015, 2017, 2016, 2017, 2013, 2017 };
            int[] months = { 12, 1, 2, 12, 5, 9, 9 };
            int[] days = { 2, 4, 1, 2, 16, 22, 1 };
            string[] genres = { "animation", "what", "what", "nowhat", "animation", "what", "horror" };
            decimal[] prices = { 20, 30, 15, 20, 19.9M, 20.1M, 0.5M };
            string[] ratings = { "G", "xxx", "xx", "fgbn", "G", "G", "N" };
            
            for (int i = 0; i < titles.Length; ++i)
            {
                context.Movies.Add(new Movie{
                    Title = titles[i],
                    ReleaseDate = new DateTime(years[i], months[i], days[i]),
                    Genre = genres[i],
                    Price = prices[i],
                    Rating = ratings[i]
                });
            }
            base.Seed(context);
        }
    }
}