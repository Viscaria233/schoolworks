using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace Test3_Movie.Models
{
    public class Movie
    {
        public int ID { get; set; }

        [Required(AllowEmptyStrings = false, ErrorMessage = "必填")]
        public string Title { get; set; }

        [DataType(DataType.Date, ErrorMessage = "字段 ReleaseDate 必须是日期")]
        [Required(AllowEmptyStrings = false, ErrorMessage = "字段 ReleaseDate 是必需的")]
        public DateTime ReleaseDate { get; set; }


        [Required(AllowEmptyStrings = false, ErrorMessage = "字段 Genre 是必需的")]
        public string Genre { get; set; }


        [Required(AllowEmptyStrings = false, ErrorMessage = "字段 Price 是必需的")]
        [Range(0, UInt64.MaxValue, ErrorMessage="字段 Price 不能为负")]
        public decimal Price { get; set; }

        [MaxLength(5, ErrorMessage="字段 Rating 必须是最大长度为5的字符串")]
        public string Rating { get; set; }
    }
}