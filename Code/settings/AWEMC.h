#ifndef AWE_MC_H
#define AWE_MC_H

// the singletons
#include "settings/AWEGlobalSettings.h"

namespace AWE
{
	/**
	 * \brief This holds a few static instances
	 *			of important classes, like
	 *			`AWE::GlobalSettings` and
	 *			`UI::Delegate`.
	 **/
	class AWEMC : public QObject
	{
		public:
			/** 
			 * \brief So that `GlobalSettings` can set
			 *			the singleton.
			 **/
			friend class AWE::GlobalSettings;

			/**
			 * \brief Get the global settings for AWEMC.
			 *
			 * \returns The global settings for AWEMC.
			 **/
			static AWE::GlobalSettings* settings();

		private:
			static AWE::GlobalSettings* mySettings;
	};
}

#endif