Metadata Scraping
==============

Metadata scrapers obtain metadata for `MetadataHolder`s with a specific type. See [the settings README][settings] for an explanation of what metadata consists of in AWEMC.

## Interfaces

There are two interfaces that you need to implement:

 - `MetadataScraperFactory`: constructs metadata scrapers from their JSON configuration file.
 - `MetadataScraper`: obtains metadata for a `MetadataHolder` and creates items in conjunction with a folder generator. The latter is not yet supported.

[settings]: <../settings/README.md>