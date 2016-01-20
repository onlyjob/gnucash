/********************************************************************
 * utest-gnc-csv-model.c: GLib g_test test suite for gnc-csv-model.c.		    *
 * Copyright 2015 Geert Janssens <geert.gnucash@kobaltwit.be>		    *
 *                                                                  *
 * This program is free software; you can redistribute it and/or    *
 * modify it under the terms of the GNU General Public License as   *
 * published by the Free Software Foundation; either version 2 of   *
 * the License, or (at your option) any later version.              *
 *                                                                  *
 * This program is distributed in the hope that it will be useful,  *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of   *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the    *
 * GNU General Public License for more details.                     *
 *                                                                  *
 * You should have received a copy of the GNU General Public License*
 * along with this program; if not, you can retrieve it from        *
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html            *
 * or contact:                                                      *
 *                                                                  *
 * Free Software Foundation           Voice:  +1-617-542-5942       *
 * 51 Franklin Street, Fifth Floor    Fax:    +1-617-542-2652       *
 * Boston, MA  02110-1301,  USA       gnu@gnu.org                   *
 ********************************************************************/
#include <config.h>
#include <string.h>
#include <glib.h>
#include <unittest-support.h>
/* Add specific headers for this class */
#include "import-export/csv-imp/gnc-csv-model.h"

typedef struct
{
} Fixture;

typedef struct
{
    int          date_fmt;
    const gchar *date_str;
    int          exp_year;
    int          exp_month;
    int          exp_day;
} parse_date_data;

static void
setup( Fixture *fixture, gconstpointer pData )
{

}

static void
teardown( Fixture *fixture, gconstpointer pData )
{
}

static const gchar *suitename = "/import-export/csv-imp/gnc-csv-model";
void test_suite_gnc_csv_model ( void );

static char* get_filepath(const char* filename, gboolean test_existence)
{
    char *result;

    const char *srcdir = g_getenv("SRCDIR");
    if (!srcdir)
    {
        g_test_message("No env variable SRCDIR exists, assuming \".\"\n");
        srcdir = ".";
    }

    result = g_strdup_printf("%s/%s", srcdir, filename);

    g_test_message("Using file path %s\n", result);

    // Test whether the file really exists
    if (test_existence)
        g_assert(g_file_test(result, G_FILE_TEST_EXISTS));

    return result;
}

/* parse_date_with_year
time64 parse_date_with_year (const char* date_str, int format)// Local: 1:0:0
*/
// Internal helper only - no tests.
/* parse_date_without_year
static time64 parse_date_without_year (const char* date_str, int format)// Local: 1:0:0
*/
// Internal helper only - no tests.

/* parse_date
time64 parse_date (const char* date_str, int format)// C: 14 in 7 SCM: 9 in 2 Local: 1:0:0
*/
static void
test_parse_date (Fixture *fixture, gconstpointer pData)
{
    time64 rawtime = gnc_time_utc (NULL);
    struct tm *tm = gnc_gmtime (&rawtime);
    int curr_year = tm->tm_year;


    /* Note: tm_year = year - 1900 and tm_mon = 0-11
     * I'm writing the expected values as subtractions for easier
     * comparison with the date string under test
     */
    parse_date_data test_dates[] =
    {
        // supported combinations  -/.'
        { 0, "2013-08-01", 2013 - 1900,  8 - 1,  1},
        { 0,  "2013-8-01", 2013 - 1900,  8 - 1,  1},
        { 0,  "2013-08-1", 2013 - 1900,  8 - 1,  1},
        { 0,   "2013-8-1", 2013 - 1900,  8 - 1,  1},
        { 0,   "13-08-01", 2013 - 1900,  8 - 1,  1},
        { 0,    "13-8-01", 2013 - 1900,  8 - 1,  1},
        { 0,    "13-08-1", 2013 - 1900,  8 - 1,  1},
        { 0,     "13-8-1", 2013 - 1900,  8 - 1,  1},
        { 0, "2009/11/04", 2009 - 1900, 11 - 1,  4},
        { 0,  "1985.3.12", 1985 - 1900,  3 - 1, 12},
        { 0,      "3'6'8", 2003 - 1900,  6 - 1,  8},
        { 0,   "20130801", 2013 - 1900,  8 - 1,  1},
        { 1, "01-08-2013", 2013 - 1900,  8 - 1,  1},
        { 1,  "01-8-2013", 2013 - 1900,  8 - 1,  1},
        { 1,  "1-08-2013", 2013 - 1900,  8 - 1,  1},
        { 1,   "1-8-2013", 2013 - 1900,  8 - 1,  1},
        { 1,   "01-08-13", 2013 - 1900,  8 - 1,  1},
        { 1,    "01-8-13", 2013 - 1900,  8 - 1,  1},
        { 1,    "1-08-13", 2013 - 1900,  8 - 1,  1},
        { 1,     "1-8-13", 2013 - 1900,  8 - 1,  1},
        { 1, "04/11/2009", 2009 - 1900, 11 - 1,  4},
        { 1,  "12.3.1985", 1985 - 1900,  3 - 1, 12},
        { 1,      "8'6'3", 2003 - 1900,  6 - 1,  8},
        { 1,   "01082013", 2013 - 1900,  8 - 1,  1},
        { 2, "08-01-2013", 2013 - 1900,  8 - 1,  1},
        { 2,  "8-01-2013", 2013 - 1900,  8 - 1,  1},
        { 2,  "08-1-2013", 2013 - 1900,  8 - 1,  1},
        { 2,   "8-1-2013", 2013 - 1900,  8 - 1,  1},
        { 2,   "08-01-13", 2013 - 1900,  8 - 1,  1},
        { 2,    "8-01-13", 2013 - 1900,  8 - 1,  1},
        { 2,    "08-1-13", 2013 - 1900,  8 - 1,  1},
        { 2,     "8-1-13", 2013 - 1900,  8 - 1,  1},
        { 2, "11/04/2009", 2009 - 1900, 11 - 1,  4},
        { 2,  "3.12.1985", 1985 - 1900,  3 - 1, 12},
        { 2,      "6'8'3", 2003 - 1900,  6 - 1,  8},
        { 2,   "08012013", 2013 - 1900,  8 - 1,  1},
        { 3,      "01-08",   curr_year,  8 - 1,  1},
        { 3,       "01-8",   curr_year,  8 - 1,  1},
        { 3,       "1-08",   curr_year,  8 - 1,  1},
        { 3,        "1-8",   curr_year,  8 - 1,  1},
        { 3,      "04/11",   curr_year, 11 - 1,  4},
        { 3,       "12.3",   curr_year,  3 - 1, 12},
        { 3,        "8'6",   curr_year,  6 - 1,  8},
        { 4,      "08-01",   curr_year,  8 - 1,  1},
        { 4,       "8-01",   curr_year,  8 - 1,  1},
        { 4,       "08-1",   curr_year,  8 - 1,  1},
        { 4,        "8-1",   curr_year,  8 - 1,  1},
        { 4,      "11/04",   curr_year, 11 - 1,  4},
        { 4,       "3.12",   curr_year,  3 - 1, 12},
        { 4,        "6'8",   curr_year,  6 - 1,  8},

        // ambiguous date formats
        // current parser doesn't know how to disambiguate
        // and hence refuses to parse
        // can possibly improved with a smarter parser
        { 0,     "130801",          -1,     -1, -1},
        { 1,     "010813",          -1,     -1, -1},
        { 2,     "080113",          -1,     -1, -1},
        { 3,       "0108",          -1,     -1, -1},
        { 4,       "0801",          -1,     -1, -1},

        // Combinations that don't make sense
        // but can still be entered by a user
        // Should ideally all result in refusal to parse...
        { 0,      "08-01",          -1,     -1, -1},
        { 0,       "0801",          -1,     -1, -1},
        { 1,      "01-08",          -1,     -1, -1},
        { 1,       "0108",          -1,     -1, -1},
        { 2,      "08-01",          -1,     -1, -1},
        { 2,       "0801",          -1,     -1, -1},
        { 3, "01-08-2013",   curr_year,  8 - 1,  1}, // BAD behavior !
        { 3,   "01-08-13",   curr_year,  8 - 1,  1}, // BAD behavior !
        { 3,   "08-08-08",   curr_year,  8 - 1,  8}, // BAD behavior !
        { 3,   "01082013",          -1,     -1, -1},
        { 3,     "010813",          -1,     -1, -1},
        { 3,   "20130108",          -1,     -1, -1},
        { 4, "08-01-2013",   curr_year,  8 - 1,  1}, // BAD behavior !
        { 4,   "08-01-13",   curr_year,  8 - 1,  1}, // BAD behavior !
        { 4, "2013-08-01",          -1,     -1, -1},
        { 4,   "09-08-01",   curr_year,  9 - 1,  8}, // BAD behavior !
        { 4,   "08012013",          -1,     -1, -1},
        { 4,     "080113",          -1,     -1, -1},
        { 4,   "20130801",          -1,     -1, -1},

        // Sentinel to mark the end of available tests
        { 0,         NULL,           0,      0,  0},

    };
    int i = 0;

    gnc_tm_free(tm);
    while (test_dates[i].date_str)
    {
        gboolean success = TRUE;
        int got_year = 0, got_month = 0, got_day = 0;

        rawtime = parse_date (test_dates[i].date_str, test_dates[i].date_fmt);
        if (rawtime == -1)
            got_year = got_month = got_day = -1;
        else
        {
            tm = gnc_gmtime (&rawtime);
            got_year = tm->tm_year;
            got_month = tm->tm_mon;
            got_day = tm->tm_mday;
            gnc_tm_free(tm);
        }

        if ((got_year  != test_dates[i].exp_year) ||
            (got_month != test_dates[i].exp_month) ||
            (got_day   != test_dates[i].exp_day))
        {
            g_error ("Parse_date failed for date '%s' and format '%d'.\n"
                            "Expected result: year %d, month %d, day %d\n"
                            "Obtained result: year %d, month %d, day %d",
                            test_dates[i].date_str,
                            test_dates[i].date_fmt,
                            test_dates[i].exp_year,
                            test_dates[i].exp_month,
                            test_dates[i].exp_day,
                            got_year, got_month, got_day);
        }

        i++;
    }


}
/* gnc_csv_parse_data_free
void gnc_csv_parse_data_free (GncCsvParseData* parse_data)// C: 3 in 1  Local: 0:0:0
*/
/* static void
test_gnc_csv_parse_data_free (Fixture *fixture, gconstpointer pData)
{
}*/
/* gnc_csv_convert_encoding
int gnc_csv_convert_encoding (GncCsvParseData* parse_data, const char* encoding,// C: 1  Local: 1:0:0
*/
/* static void
test_gnc_csv_convert_encoding (Fixture *fixture, gconstpointer pData)
{
}*/
/* gnc_csv_load_file
int gnc_csv_load_file (GncCsvParseData* parse_data, const char* filename,// C: 1  Local: 0:0:0
*/
/* static void
test_gnc_csv_load_file (Fixture *fixture, gconstpointer pData)
{
}*/
/* gnc_csv_parse
int gnc_csv_parse (GncCsvParseData* parse_data, gboolean guessColTypes, GError** error)// C: 13 in 1  Local: 0:0:0
*/
static void
test_gnc_csv_parse (Fixture *fixture, gconstpointer pData)
{

    char *file1 = get_filepath ("notexist.csv", FALSE);
    char *file2 = get_filepath ("sample1.csv", TRUE);
    GError *the_error = NULL;
    int resultcode = 0;

    GncCsvParseData* parse_data = gnc_csv_new_parse_data ();

    /* Test if object creation worked */
    g_assert (parse_data != NULL);

    /* Test loading of a non-existing file */
    resultcode = gnc_csv_load_file (parse_data, file1,
                                    &the_error);
    g_assert ((the_error->domain == GNC_CSV_IMP_ERROR) &&
              (the_error->code == GNC_CSV_IMP_ERROR_OPEN));

    /* Test loading of a valid csv file */
    resultcode = gnc_csv_load_file (parse_data, file2,
                                        &the_error);
    g_assert (resultcode == 0);

    /* Test basic parsing of the loaded file
     * A few fields are sampled in the parsed data. */
    resultcode = gnc_csv_parse (parse_data, TRUE, &the_error);
    g_assert (g_strcmp0 ((char*)((GPtrArray*)(parse_data->orig_lines->pdata[0]))->pdata[0],
                         "Date") == 0);
    g_assert (g_strcmp0 ((char*)((GPtrArray*)(parse_data->orig_lines->pdata[1]))->pdata[6],
                         "1,100.00") == 0);

    /* Clean up */
    g_free(file1);
    g_free(file2);
    gnc_csv_parse_data_free (parse_data);
}
/* trans_property_free
static void trans_property_free (TransProperty* prop)// Local: 2:0:0
*/
/* static void
test_trans_property_free (Fixture *fixture, gconstpointer pData)
{
}*/
/* trans_property_set
static gboolean trans_property_set (TransProperty* prop, char* str)// Local: 1:0:0
*/
/* static void
test_trans_property_set (Fixture *fixture, gconstpointer pData)
{
}*/
/* trans_property_list_free
static void trans_property_list_free (TransPropertyList* list)// Local: 1:0:0
*/
/* static void
test_trans_property_list_free (Fixture *fixture, gconstpointer pData)
{
}*/
/* trans_property_list_add
static void trans_property_list_add (TransProperty* property)// Local: 1:0:0
*/
/* static void
test_trans_property_list_add (Fixture *fixture, gconstpointer pData)
{
}*/
/* trans_add_split
static void trans_add_split (Transaction* trans, Account* account, QofBook* book,// Local: 2:0:0
*/
/* static void
test_trans_add_split (Fixture *fixture, gconstpointer pData)
{
}*/
/* trans_property_list_verify_essentials
static gboolean trans_property_list_verify_essentials (TransPropertyList* list, gchar** error)// Local: 1:0:0
*/
/* static void
test_trans_property_list_verify_essentials (Fixture *fixture, gconstpointer pData)
{
}*/
/* gnc_csv_parse_to_trans
int gnc_csv_parse_to_trans (GncCsvParseData* parse_data, Account* account,// C: 2 in 1  Local: 0:0:0
*/
/* static void
test_gnc_csv_parse_to_trans (Fixture *fixture, gconstpointer pData)
{
}*/


void
test_suite_gnc_csv_model (void)
{

// GNC_TEST_ADD (suitename, "parse date with year", Fixture, NULL, setup, test_parse_date_with_year, teardown);
// GNC_TEST_ADD (suitename, "parse date without year", Fixture, NULL, setup, test_parse_date_without_year, teardown);
GNC_TEST_ADD (suitename, "parse date", Fixture, NULL, NULL, test_parse_date, NULL);
// GNC_TEST_ADD (suitename, "gnc csv parse data free", Fixture, NULL, setup, test_gnc_csv_parse_data_free, teardown);
// GNC_TEST_ADD (suitename, "gnc csv convert encoding", Fixture, NULL, setup, test_gnc_csv_convert_encoding, teardown);
// GNC_TEST_ADD (suitename, "gnc csv load file", Fixture, NULL, setup, test_gnc_csv_load_file, teardown);
GNC_TEST_ADD (suitename, "gnc csv parse", Fixture, NULL, setup, test_gnc_csv_parse, teardown);
// GNC_TEST_ADD (suitename, "trans property free", Fixture, NULL, setup, test_trans_property_free, teardown);
// GNC_TEST_ADD (suitename, "trans property set", Fixture, NULL, setup, test_trans_property_set, teardown);
// GNC_TEST_ADD (suitename, "trans property list free", Fixture, NULL, setup, test_trans_property_list_free, teardown);
// GNC_TEST_ADD (suitename, "trans property list add", Fixture, NULL, setup, test_trans_property_list_add, teardown);
// GNC_TEST_ADD (suitename, "trans add split", Fixture, NULL, setup, test_trans_add_split, teardown);
// GNC_TEST_ADD (suitename, "trans property list verify essentials", Fixture, NULL, setup, test_trans_property_list_verify_essentials, teardown);
// GNC_TEST_ADD (suitename, "gnc csv parse to trans", Fixture, NULL, setup, test_gnc_csv_parse_to_trans, teardown);

}