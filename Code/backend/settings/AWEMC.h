#ifndef AWE_MC_H
#define AWE_MC_H

// library macros
#include "macros/BackendLibraryMacros.h"

// the singletons
#include "settings/GlobalSettings.h"

namespace AWE {
	/**
	 * \brief This holds a few static instances
     *		  of important classes, like
     *		  `AWE::GlobalSettings` and
     *		  `UI::Delegate` (eventually).
     */
    class AWEMC_BACKEND_LIBRARY AWEMC : public QObject {
		public:
			/** 
			 * \brief So that `GlobalSettings` can set
			 *			the singleton.
             */
			friend class GlobalSettings;

			/**
			 * \brief Get the global settings for AWEMC.
			 *
			 * \returns The global settings for AWEMC.
             */
			static GlobalSettings* settings();

		private:
			AWEMC();
			static GlobalSettings* mySettings;
	};
}

#endif
