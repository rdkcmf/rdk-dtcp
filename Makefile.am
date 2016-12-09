##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2016 RDK Management
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
##########################################################################
SUBDIRS = @SUBDIRS@
DIST_SUBDIRS = cfg @SUBDIRS@

distcleancheck_listfiles = *-libtool

## IPK Generation Support
dtcpmgr_IPK_OUTDIR = $(abs_top_builddir)/ipk
dtcpmgr_IPK_STAGING_DIR=$(abs_top_builddir)/staging_dir
dtcpmgr_IPK_TMP_DIR = $(dtcpmgr_IPK_STAGING_DIR)/ipk
dtcpmgr_CONTROL_FILES = control
dtcpmgr_IPK_FILES  = debian-binary control.tar.gz data.tar.gz
dtcpmgr_IPK_OUTPUT = libdtcpmgr.ipk

package_ipk:
	@echo "Generating IPK Package"
	## Install files
	$(MAKE) prefix=$(dtcpmgr_IPK_STAGING_DIR) install
	## Create temp paths
	$(mkdir_p) $(dtcpmgr_IPK_TMP_DIR)/usr/lib
	## Install files to temp path
	cp -af $(dtcpmgr_IPK_STAGING_DIR)/lib/*.so* $(dtcpmgr_IPK_TMP_DIR)/usr/lib/
	## Create package files
	tar -czvf $(dtcpmgr_IPK_OUTDIR)/data.tar.gz -C $(dtcpmgr_IPK_TMP_DIR) usr
	tar -czvf $(dtcpmgr_IPK_OUTDIR)/control.tar.gz -C $(dtcpmgr_IPK_OUTDIR) $(dtcpmgr_CONTROL_FILES)
	cd $(dtcpmgr_IPK_OUTDIR) && ar cr $(dtcpmgr_IPK_OUTPUT) $(dtcpmgr_IPK_FILES) && cd -
	rm -rf $(dtcpmgr_IPK_TMP_DIR)
	rm -f $(dtcpmgr_IPK_OUTDIR)/*.tar.gz
clean_package_ipk:
	rm -rf $(dtcpmgr_IPK_STAGING_DIR)
	rm -f $(dtcpmgr_IPK_OUTDIR)/*.tar.gz
