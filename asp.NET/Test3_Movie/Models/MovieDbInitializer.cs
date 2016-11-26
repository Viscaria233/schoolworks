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
            context.Movies.Add(new Movie {
                Title = "你的名字",
                ReleaseDate = new DateTime(2016, 12, 2),
                Genre = "animation",
                Price = 20,
                Rating = "G"
            }); 
            base.Seed(context);
        }
    }
}