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
        private static Stack<List<Movie>> searchHistory = new Stack<List<Movie>>();
        private static Stack<SearchInput> inputHistory = new Stack<SearchInput>();

        //
        // GET: /Home/

        public ActionResult Index()
        {
            if (inputHistory.Count == 0)
            {
                ViewData["Input"] = new SearchInput();
            }
            else
            {
                ViewData["Input"] = inputHistory.Peek();
            }

            if (searchHistory.Count == 0)
            {
                return View(db.Movies.ToList());
            }
            else
            {
                var peek = searchHistory.Peek();
                return View(peek);
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
        public ActionResult Search()
        {
            var minPrice = Request.Form["S_MinPrice"];
            var maxPrice = Request.Form["S_MaxPrice"];

            var input = new SearchInput
            {
                genre = Request.Form["S_Genre"],
                title = Request.Form["S_Title"],
                released = Int32.Parse(Request.Form["S_Released"]),
                minPrice = minPrice != "" ? Decimal.Parse(minPrice) : 0,
                maxPrice = maxPrice != "" ? Decimal.Parse(maxPrice) : 0,
                includeMin = Boolean.Parse(Request.Form["S_IncludeMin"]),
                includeMax = Boolean.Parse(Request.Form["S_IncludeMax"]),
                validMin = minPrice != "",
                validMax = maxPrice != ""
            };
            inputHistory.Push(input);
            var searchUtil = new SearchUtil { input = input };
            var result = searchUtil.search(searchHistory.Count != 0 ?
                searchHistory.Peek() : db.Movies.ToList());
            searchHistory.Push(result);

            return RedirectToAction("Index");
        }

        public ActionResult ShowAllMovies()
        {
            searchHistory.Clear();
            inputHistory.Clear();
            return RedirectToAction("Index");
        }

        public ActionResult Back()
        {
            if (searchHistory.Count != 0)
            {
                searchHistory.Pop();
            }
            if (inputHistory.Count != 0)
            {
                inputHistory.Pop();
            }
            return RedirectToAction("Index");
        }
    }
}