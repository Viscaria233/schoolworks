using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Web;

namespace Test3_Movie.Models
{
    public class MovieDbContext : DbContext
    {
        public MovieDbContext() : base("DefaultConnection") { }

        public DbSet<Movie> Movies { get; set; }
    }
}