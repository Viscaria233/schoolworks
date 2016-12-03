using System;
using System.Collections.Generic;
using System.Data;
using System.Data.Entity;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using Test3_Movie.Models;

namespace Test3_Movie.Controllers
{
    public class HomeController : Controller
    {
        private MovieDbContext db = new MovieDbContext();
        private static List<int> searchResultID = null;

        //
        // GET: /Home/

        public ActionResult Index()
        {
            if (searchResultID == null)
            {
                return View(db.Movies.ToList());
            }
            else
            {
                var list = from m in db.Movies
                           where searchResultID.Contains(m.ID)
                           select m;
                return View(list);
            }
            
        }

        //
        // GET: /Home/Details/5

        public ActionResult Details(int id = 0)
        {
            Movie movie = db.Movies.Find(id);
            if (movie == null)
            {
                return HttpNotFound();
            }
            return View(movie);
        }

        //
        // GET: /Home/Create

        public ActionResult Create()
        {
            return View();
        }

        //
        // POST: /Home/Create

        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Create(Movie movie)
        {
            if (ModelState.IsValid)
            {
                db.Movies.Add(movie);
                db.SaveChanges();
                return RedirectToAction("ShowAllMovies");
            }

            return View(movie);
        }

        //
        // GET: /Home/Edit/5

        public ActionResult Edit(int id = 0)
        {
            Movie movie = db.Movies.Find(id);
            if (movie == null)
            {
                return HttpNotFound();
            }
            return View(movie);
        }

        //
        // POST: /Home/Edit/5

        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Edit(Movie movie)
        {
            if (ModelState.IsValid)
            {
                db.Entry(movie).State = EntityState.Modified;
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            return View(movie);
        }

        //
        // GET: /Home/Delete/5

        public ActionResult Delete(int id = 0)
        {
            Movie movie = db.Movies.Find(id);
            if (movie == null)
            {
                return HttpNotFound();
            }
            return View(movie);
        }

        //
        // POST: /Home/Delete/5

        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public ActionResult DeleteConfirmed(int id)
        {
            Movie movie = db.Movies.Find(id);
            db.Movies.Remove(movie);
            db.SaveChanges();
            return RedirectToAction("Index");
        }

        protected override void Dispose(bool disposing)
        {
            db.Dispose();
            base.Dispose(disposing);
        }

        [HttpPost]
        public ActionResult SearchByGenreAndTitle()
        {
            var genre = Request.Form["S_Genre"];
            var title = Request.Form["S_Title"];
            var result = from m in db.Movies
                         where (genre == "all" || m.Genre.Equals(genre))
                                && m.Title.Contains(title)
                         select m.ID;
            searchResultID = result.ToList();
            return RedirectToAction("Index");
        }

        [HttpPost]
        public ActionResult SearchByReleased()
        {
            bool released = Boolean.Parse(Request.Form["S_Released"]);
            var result = from m in db.Movies
                         where DateTime.Now.CompareTo(m.ReleaseDate) * (released ? 1 : -1) > 0
                         select m.ID;
            searchResultID = result.ToList();
            return RedirectToAction("Index");
        }

        [HttpPost]
        public ActionResult SearchByPrice()
        {
            var minPrice = Request.Form["S_MinPrice"];
            var maxPrice = Request.Form["S_MaxPrice"];
            if (minPrice != "" && maxPrice != "")
            {
                decimal min = Decimal.Parse(minPrice);
                decimal max = Decimal.Parse(maxPrice);
                var result = from m in db.Movies
                             where m.Price >= min && m.Price <= max
                             select m.ID;
                searchResultID = result.ToList();
            }
            else if (minPrice != "")
            {
                decimal min = Decimal.Parse(minPrice);
                var result = from m in db.Movies
                             where m.Price >= min
                             select m.ID;
                searchResultID = result.ToList();
            }
            else
            {
                decimal max = Decimal.Parse(maxPrice);
                var result = from m in db.Movies
                             where m.Price <= max
                             select m.ID;
                searchResultID = result.ToList();
            }
            return RedirectToAction("Index");
        }

        public ActionResult ShowAllMovies()
        {
            searchResultID = null;
            return RedirectToAction("Index");
        }
    }
}