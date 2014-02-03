CURIOS: Linked Data CMS
=======================

*CURIOS: Linked Data CMS* is a Drupal 7 module that provides the functionality to perform CRUD operations on RDF data stored in a triple store. The module makes use of a configuration that provides a mapping between OWL classes/properties and Drupal entities.

This version of the module is intended for use with the [Hebridean Connections](http://blog.hebrideanconnections.com/)
case study for the [CURIOS project](http://www.dotrural.ac.uk/curios).

### Requirements:
  * Drupal 7.23+
  * Apache, MySQL, PHP 5.4+
  * wget, git, [drush](http://drush.ws/)
  * [msysgit](http://msysgit.github.io/) (for Microsoft Windows installation)
  * Jena Fuseki 1.0.0+ - http://jena.apache.org/documentation/serving_data/

### Useful documentation:
  * [Drupal System Requirements](https://drupal.org/requirements)
  * [Drupal Installation Guide](https://drupal.org/documentation/install)
  * [Installing Drupal modules and themes](https://drupal.org/documentation/install/modules-themes)

### Required modules, stable releases:
The module has been tested with the following stable releases. It may also work with newer releases originating from the same branch --
**drush** should install these dependencies automatically when the module is enabled.

  Module Name | Release Download
  --- | ---
  [Entity](https://drupal.org/project/entity)       | [7.x-1.2](http://ftp.drupal.org/files/projects/entity-7.x-1.2.tar.gz)
  [Views](https://drupal.org/project/views)         | [7.x-3.7](http://ftp.drupal.org/files/projects/views-7.x-3.7.tar.gz)
  [CTools](https://drupal.org/project/ctools)       | [7.x-1.3](http://ftp.drupal.org/files/projects/ctools-7.x-1.3.tar.gz)
  [Lightbox2](https://drupal.org/project/lightbox2) | [7.x-1.0-beta1](http://ftp.drupal.org/files/projects/lightbox2-7.x-1.0-beta1.tar.gz)
  [Ckeditor](https://drupal.org/project/ckeditor)   | [7.x-1.13](http://ftp.drupal.org/files/projects/ckeditor-7.x-1.13.tar.gz)
  [Libraries](https://drupal.org/project/libraries) | [7.x-2.1](http://ftp.drupal.org/files/projects/libraries-7.x-2.1.tar.gz)
  [Views Litepager](https://drupal.org/project/views_litepager) | [7.x-3.0](http://ftp.drupal.org/files/projects/views_litepager-7.x-3.0.tar.gz)
  [Imagecache External](https://drupal.org/project/imagecache_external) | [7.x-2.0-beta1](http://ftp.drupal.org/files/projects/imagecache_external-7.x-2.0-beta1.tar.gz)
  [Devel](https://drupal.org/project/devel)         | [7.x-1.3](http://ftp.drupal.org/files/projects/devel-7.x-1.3.tar.gz)

### Required modules, development snapshots:
These modules should be downloaded manually and extracted to the appropriate directory, either by using the download links below, or by using git to pull the latest development version.

  Module Name | Snapshot Download | Module Directory
  --- | --- | ---
  [Panels](https://drupal.org/project/panels)               | [7.x-3.x-dev](http://ftp.drupal.org/files/projects/panels-7.x-3.x-dev.tar.gz) | panels
  [RDFx](https://drupal.org/project/rdfx)                   | [7.x-2.x-dev](http://ftp.drupal.org/files/projects/rdfx-7.x-2.x-dev.tar.gz) | rdfx
  [SPARQL](https://github.com/stuartraetaylor/sparql)       | [sparql11-0.1.0](https://github.com/stuartraetaylor/sparql/archive/sparql11-0.1.0.tar.gz) | sparql
  [SPARQL Views](https://github.com/stuartraetaylor/sparql_views) | [curios-0.1.0](https://github.com/stuartraetaylor/sparql_views/archive/curios-0.1.0.tar.gz) | sparql_views
  [CURIOS: Linked Data CMS](https://github.com/curiosproject/curios) | [master](https://github.com/curiosproject/curios/archive/master.zip) | curios

### Other dependencies:
The CURIOS module also relies on modified versions of the ARC2 PHP library and Drupal 7 theme.

  Name | Download | Description
  --- | --- | ---
  [ARC2 library](https://github.com/stuartraetaylor/arc2-sparql11)  | [sparql11-0.1.0](https://github.com/stuartraetaylor/arc2-sparql11/archive/sparql11-0.1.0.tar.gz) | ARC2 PHP library with support for SPARQL 1.1 remote stores.
  [CURIOS theme](https://github.com/curiosproject/curios_theme)     | [master](https://github.com/curiosproject/curios_theme/archive/master.zip) | Hebridean Connections Drupal 7 theme.


Installation Notes
------------------

### Clean install:
  1. Install Drupal 7 - standard installation.
  2. Download the **required Drupal modules**.
  3. Download the **CURIOS theme** and extract it to:

 *DRUPAL_ROOT/sites/all/themes/curios_theme*
  4. Download **arc2-sparql11** and extract it to:

   *DRUPAL_ROOT/sites/all/libraries/ARC2/arc*
  5. Enable the CURIOS module:

         $ drush -v en curios
  6. Load configuration and install CMS entities:
    * Navigate to *Structure > Linked Data CMS settings* (admin/structure/ldcms),
    * Click *Load Configuration*.
  7. Enable CURIOS Theme and set as default via admin/appearance.
  8. Enable *Description Link Filter* for *Filtered HTML* and *Full HTML* via admin/config/content/formats.
  9. Add `www.dotrural.ac.uk` to the Imagecache External whitelist (admin/config/media/imagecache_external).
  10. Download and install the standalone CKEditor to the libraries folder as described in:
    http://docs.cksource.com/CKEditor_for_Drupal/Open_Source/Drupal_7/Installation
  11. Optional: enable *Cache pages for anonymous users* via admin/config/development/performance.
  12. Finally, clear Drupal's cache:

          $ drush cc all

### Major update (changes to dataset or module structure):
  *Steps 1--2 should be performed before updating the module.*

  1. Uninstall CMS entities:
    * Navigate to *Structure > Linked Data CMS settings* (admin/structure/ldcms),
    * Under *Advanced Options*, check *Remove fields only*,
    * Click *Load Configuration*.
  2. Disable and uninstall the CURIOS module:

         $ drush dis curios
         $ drush pm-uninstall curios
  3. Pull the latest version of the CURIOS module from GitHub (or download the .zip):

         $ cd sites/all/modules/curios
         $ git pull origin master
  4. Enable CURIOS module:

         $ drush en curios
  5. Load configuration and install new CMS entities:
    * Navigate to *Structure > Linked Data CMS settings* (admin/structure/ldcms),
    * Click *Load Configuration*.
  6. Clear Drupal's cache:

         $ drush cc all
