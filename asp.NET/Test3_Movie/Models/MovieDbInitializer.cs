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
            context.Movies.Add(new Movie
            {
                Title = "AAA",
                ReleaseDate = new DateTime(2015, 1, 4),
                Genre = "what",
                Price = 30,
                Rating = "xxx"
            });
            context.Movies.Add(new Movie
            {
                Title = "CCCCC",
                ReleaseDate = new DateTime(2017, 2, 1),
                Genre = "what",
                Price = 15,
                Rating = "xx"
            });
            context.Movies.Add(new Movie
            {
                Title = "bbbAAAb",
                ReleaseDate = new DateTime(2016, 12, 2),
                Genre = "nowhat",
                Price = 20,
                Rating = "fgbn"
            }); 
            base.Seed(context);
        }
    }
}