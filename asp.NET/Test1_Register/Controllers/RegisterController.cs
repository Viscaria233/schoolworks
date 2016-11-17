using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Text.RegularExpressions;
using Test1_Register.Models;

namespace Test1_Register.Controllers
{
    public class RegisterController : Controller
    {
        //
        // GET: /Register/

        public ActionResult Index()
        {
            return View();
        }

        public ActionResult Register(User user)
        {
            HttpPostedFileBase file = Request.Files["photo"];
            if (file != null)
            {
                string fileName = Regex.Replace(Path.GetFileName(file.FileName), "\\s+", "_");
                string path = Path.Combine(Request.MapPath("~/Content/uploads/photos"), fileName);
                try
                {
                    file.SaveAs(path);
                    user.photo = "../Content/uploads/photos/" + fileName;
                }
                catch {}
            }
            user.hobbies = Request.Form["hobbies"];
            return View(user);
        }
    }
}
