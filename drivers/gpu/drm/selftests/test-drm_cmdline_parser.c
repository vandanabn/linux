// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2019 Bootlin
 */

#define pr_fmt(fmt) "drm_cmdline: " fmt

#include <linux/kernel.h>
#include <linux/module.h>

#include <drm/drm_connector.h>
#include <drm/drm_modes.h>

#define TESTS "drm_cmdline_selftests.h"
#include "drm_selftest.h"
#include "test-drm_modeset_common.h"

static int drm_cmdline_test_res(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(!drm_mode_parse_command_line_for_connector("720x480",
							   &connector,
							   &mode));
	FAIL_ON(!mode.specified);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);

	FAIL_ON(mode.refresh_specified);

	FAIL_ON(mode.bpp_specified);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.interlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.force != DRM_FORCE_UNSPECIFIED);

	return 0;
}

static int drm_cmdline_test_res_missing_x(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(drm_mode_parse_command_line_for_connector("x480",
							  &connector,
							  &mode));

	return 0;
}

static int drm_cmdline_test_res_missing_y(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(drm_mode_parse_command_line_for_connector("1024x",
							  &connector,
							  &mode));

	return 0;
}

static int drm_cmdline_test_res_bad_y(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(drm_mode_parse_command_line_for_connector("1024xtest",
							  &connector,
							  &mode));

	return 0;
}

static int drm_cmdline_test_res_missing_y_bpp(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(drm_mode_parse_command_line_for_connector("1024x-24",
							  &connector,
							  &mode));

	return 0;
}

static int drm_cmdline_test_res_vesa(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(!drm_mode_parse_command_line_for_connector("720x480M",
							   &connector,
							   &mode));
	FAIL_ON(!mode.specified);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);

	FAIL_ON(mode.refresh_specified);

	FAIL_ON(mode.bpp_specified);

	FAIL_ON(mode.rb);
	FAIL_ON(!mode.cvt);
	FAIL_ON(mode.interlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.force != DRM_FORCE_UNSPECIFIED);

	return 0;
}

static int drm_cmdline_test_res_vesa_rblank(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(!drm_mode_parse_command_line_for_connector("720x480MR",
							   &connector,
							   &mode));
	FAIL_ON(!mode.specified);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);

	FAIL_ON(mode.refresh_specified);

	FAIL_ON(mode.bpp_specified);

	FAIL_ON(!mode.rb);
	FAIL_ON(!mode.cvt);
	FAIL_ON(mode.interlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.force != DRM_FORCE_UNSPECIFIED);

	return 0;
}

static int drm_cmdline_test_res_rblank(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(!drm_mode_parse_command_line_for_connector("720x480R",
							   &connector,
							   &mode));
	FAIL_ON(!mode.specified);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);

	FAIL_ON(mode.refresh_specified);

	FAIL_ON(mode.bpp_specified);

	FAIL_ON(!mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.interlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.force != DRM_FORCE_UNSPECIFIED);

	return 0;
}

static int drm_cmdline_test_res_bpp(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(!drm_mode_parse_command_line_for_connector("720x480-24",
							   &connector,
							   &mode));
	FAIL_ON(!mode.specified);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);

	FAIL_ON(mode.refresh_specified);

	FAIL_ON(!mode.bpp_specified);
	FAIL_ON(mode.bpp != 24);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.interlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.force != DRM_FORCE_UNSPECIFIED);

	return 0;
}

static int drm_cmdline_test_res_bad_bpp(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(drm_mode_parse_command_line_for_connector("720x480-test",
							  &connector,
							  &mode));

	return 0;
}

static int drm_cmdline_test_res_refresh(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(!drm_mode_parse_command_line_for_connector("720x480@60",
							   &connector,
							   &mode));
	FAIL_ON(!mode.specified);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);

	FAIL_ON(!mode.refresh_specified);
	FAIL_ON(mode.refresh != 60);

	FAIL_ON(mode.bpp_specified);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.interlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.force != DRM_FORCE_UNSPECIFIED);

	return 0;
}

static int drm_cmdline_test_res_bad_refresh(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(drm_mode_parse_command_line_for_connector("720x480@refresh",
							  &connector,
							  &mode));

	return 0;
}

static int drm_cmdline_test_res_bpp_refresh(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(!drm_mode_parse_command_line_for_connector("720x480-24@60",
							   &connector,
							   &mode));
	FAIL_ON(!mode.specified);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);

	FAIL_ON(!mode.refresh_specified);
	FAIL_ON(mode.refresh != 60);

	FAIL_ON(!mode.bpp_specified);
	FAIL_ON(mode.bpp != 24);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.interlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.force != DRM_FORCE_UNSPECIFIED);

	return 0;
}

static int drm_cmdline_test_res_bpp_refresh_interlaced(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(!drm_mode_parse_command_line_for_connector("720x480-24@60i",
							   &connector,
							   &mode));
	FAIL_ON(!mode.specified);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);

	FAIL_ON(!mode.refresh_specified);
	FAIL_ON(mode.refresh != 60);

	FAIL_ON(!mode.bpp_specified);
	FAIL_ON(mode.bpp != 24);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(!mode.interlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.force != DRM_FORCE_UNSPECIFIED);

	return 0;
}

static int drm_cmdline_test_res_bpp_refresh_margins(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(!drm_mode_parse_command_line_for_connector("720x480-24@60m",
							   &connector,
							   &mode));
	FAIL_ON(!mode.specified);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);

	FAIL_ON(!mode.refresh_specified);
	FAIL_ON(mode.refresh != 60);

	FAIL_ON(!mode.bpp_specified);
	FAIL_ON(mode.bpp != 24);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.interlace);
	FAIL_ON(!mode.margins);
	FAIL_ON(mode.force != DRM_FORCE_UNSPECIFIED);

	return 0;
}

static int drm_cmdline_test_res_bpp_refresh_force_off(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(!drm_mode_parse_command_line_for_connector("720x480-24@60d",
							   &connector,
							   &mode));
	FAIL_ON(!mode.specified);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);

	FAIL_ON(!mode.refresh_specified);
	FAIL_ON(mode.refresh != 60);

	FAIL_ON(!mode.bpp_specified);
	FAIL_ON(mode.bpp != 24);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.interlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.force != DRM_FORCE_OFF);

	return 0;
}

static int drm_cmdline_test_res_bpp_refresh_force_on_off(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(drm_mode_parse_command_line_for_connector("720x480-24@60de",
							  &connector,
							  &mode));

	return 0;
}

static int drm_cmdline_test_res_bpp_refresh_force_on(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(!drm_mode_parse_command_line_for_connector("720x480-24@60e",
							   &connector,
							   &mode));
	FAIL_ON(!mode.specified);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);

	FAIL_ON(!mode.refresh_specified);
	FAIL_ON(mode.refresh != 60);

	FAIL_ON(!mode.bpp_specified);
	FAIL_ON(mode.bpp != 24);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.interlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.force != DRM_FORCE_ON);

	return 0;
}

static int drm_cmdline_test_res_bpp_refresh_force_on_analog(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(!drm_mode_parse_command_line_for_connector("720x480-24@60D",
							   &connector,
							   &mode));
	FAIL_ON(!mode.specified);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);

	FAIL_ON(!mode.refresh_specified);
	FAIL_ON(mode.refresh != 60);

	FAIL_ON(!mode.bpp_specified);
	FAIL_ON(mode.bpp != 24);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.interlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.force != DRM_FORCE_ON);

	return 0;
}

static int drm_cmdline_test_res_bpp_refresh_force_on_digital(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	connector.connector_type = DRM_MODE_CONNECTOR_DVII;
	FAIL_ON(!drm_mode_parse_command_line_for_connector("720x480-24@60D",
							   &connector,
							   &mode));
	FAIL_ON(!mode.specified);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);

	FAIL_ON(!mode.refresh_specified);
	FAIL_ON(mode.refresh != 60);

	FAIL_ON(!mode.bpp_specified);
	FAIL_ON(mode.bpp != 24);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.interlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.force != DRM_FORCE_ON_DIGITAL);

	return 0;
}

static int drm_cmdline_test_res_bpp_refresh_interlaced_margins_force_on(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(!drm_mode_parse_command_line_for_connector("720x480-24@60ime",
							   &connector,
							   &mode));
	FAIL_ON(!mode.specified);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);

	FAIL_ON(!mode.refresh_specified);
	FAIL_ON(mode.refresh != 60);

	FAIL_ON(!mode.bpp_specified);
	FAIL_ON(mode.bpp != 24);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(!mode.interlace);
	FAIL_ON(!mode.margins);
	FAIL_ON(mode.force != DRM_FORCE_ON);

	return 0;
}

static int drm_cmdline_test_res_margins_force_on(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(!drm_mode_parse_command_line_for_connector("720x480me",
							   &connector,
							   &mode));
	FAIL_ON(!mode.specified);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);

	FAIL_ON(mode.refresh_specified);

	FAIL_ON(mode.bpp_specified);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.interlace);
	FAIL_ON(!mode.margins);
	FAIL_ON(mode.force != DRM_FORCE_ON);

	return 0;
}

static int drm_cmdline_test_res_vesa_margins(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(!drm_mode_parse_command_line_for_connector("720x480Mm",
							   &connector,
							   &mode));
	FAIL_ON(!mode.specified);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);

	FAIL_ON(mode.refresh_specified);

	FAIL_ON(mode.bpp_specified);

	FAIL_ON(mode.rb);
	FAIL_ON(!mode.cvt);
	FAIL_ON(mode.interlace);
	FAIL_ON(!mode.margins);
	FAIL_ON(mode.force != DRM_FORCE_UNSPECIFIED);

	return 0;
}

static int drm_cmdline_test_res_invalid_mode(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(drm_mode_parse_command_line_for_connector("720x480f",
							  &connector,
							  &mode));

	return 0;
}

static int drm_cmdline_test_res_bpp_wrong_place_mode(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(drm_mode_parse_command_line_for_connector("720x480e-24",
							  &connector,
							  &mode));

	return 0;
}

static int drm_cmdline_test_name(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(!drm_mode_parse_command_line_for_connector("NTSC",
							   &connector,
							   &mode));
	FAIL_ON(strcmp(mode.name, "NTSC"));
	FAIL_ON(mode.refresh_specified);
	FAIL_ON(mode.bpp_specified);

	return 0;
}

static int drm_cmdline_test_name_bpp(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(!drm_mode_parse_command_line_for_connector("NTSC-24",
							   &connector,
							   &mode));
	FAIL_ON(strcmp(mode.name, "NTSC"));

	FAIL_ON(mode.refresh_specified);

	FAIL_ON(!mode.bpp_specified);
	FAIL_ON(mode.bpp != 24);

	return 0;
}

static int drm_cmdline_test_name_bpp_refresh(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(drm_mode_parse_command_line_for_connector("NTSC-24@60",
							  &connector,
							  &mode));

	return 0;
}

static int drm_cmdline_test_name_refresh(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(drm_mode_parse_command_line_for_connector("NTSC@60",
							  &connector,
							  &mode));

	return 0;
}

static int drm_cmdline_test_name_refresh_wrong_mode(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(drm_mode_parse_command_line_for_connector("NTSC@60m",
							  &connector,
							  &mode));

	return 0;
}

static int drm_cmdline_test_name_refresh_invalid_mode(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(drm_mode_parse_command_line_for_connector("NTSC@60f",
							  &connector,
							  &mode));

	return 0;
}

static int drm_cmdline_test_name_option(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(!drm_mode_parse_command_line_for_connector("NTSC,rotate=180",
							   &connector,
							   &mode));
	FAIL_ON(!mode.specified);
	FAIL_ON(strcmp(mode.name, "NTSC"));
	FAIL_ON(mode.rotation_reflection != DRM_MODE_ROTATE_180);

	return 0;
}

static int drm_cmdline_test_name_bpp_option(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(!drm_mode_parse_command_line_for_connector("NTSC-24,rotate=180",
							   &connector,
							   &mode));
	FAIL_ON(!mode.specified);
	FAIL_ON(strcmp(mode.name, "NTSC"));
	FAIL_ON(mode.rotation_reflection != DRM_MODE_ROTATE_180);
	FAIL_ON(!mode.bpp_specified);
	FAIL_ON(mode.bpp != 24);

	return 0;
}

static int drm_cmdline_test_rotate_0(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(!drm_mode_parse_command_line_for_connector("720x480,rotate=0",
							   &connector,
							   &mode));
	FAIL_ON(!mode.specified);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);
	FAIL_ON(mode.rotation_reflection != DRM_MODE_ROTATE_0);

	FAIL_ON(mode.refresh_specified);

	FAIL_ON(mode.bpp_specified);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.interlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.force != DRM_FORCE_UNSPECIFIED);

	return 0;
}

static int drm_cmdline_test_rotate_90(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(!drm_mode_parse_command_line_for_connector("720x480,rotate=90",
							   &connector,
							   &mode));
	FAIL_ON(!mode.specified);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);
	FAIL_ON(mode.rotation_reflection != DRM_MODE_ROTATE_90);

	FAIL_ON(mode.refresh_specified);

	FAIL_ON(mode.bpp_specified);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.interlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.force != DRM_FORCE_UNSPECIFIED);

	return 0;
}

static int drm_cmdline_test_rotate_180(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(!drm_mode_parse_command_line_for_connector("720x480,rotate=180",
							   &connector,
							   &mode));
	FAIL_ON(!mode.specified);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);
	FAIL_ON(mode.rotation_reflection != DRM_MODE_ROTATE_180);

	FAIL_ON(mode.refresh_specified);

	FAIL_ON(mode.bpp_specified);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.interlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.force != DRM_FORCE_UNSPECIFIED);

	return 0;
}

static int drm_cmdline_test_rotate_270(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(!drm_mode_parse_command_line_for_connector("720x480,rotate=270",
							   &connector,
							   &mode));
	FAIL_ON(!mode.specified);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);
	FAIL_ON(mode.rotation_reflection != DRM_MODE_ROTATE_270);

	FAIL_ON(mode.refresh_specified);

	FAIL_ON(mode.bpp_specified);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.interlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.force != DRM_FORCE_UNSPECIFIED);

	return 0;
}

static int drm_cmdline_test_rotate_invalid_val(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(drm_mode_parse_command_line_for_connector("720x480,rotate=42",
							  &connector,
							  &mode));

	return 0;
}

static int drm_cmdline_test_rotate_truncated(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(drm_mode_parse_command_line_for_connector("720x480,rotate=",
							  &connector,
							  &mode));

	return 0;
}

static int drm_cmdline_test_hmirror(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(!drm_mode_parse_command_line_for_connector("720x480,reflect_x",
							   &connector,
							   &mode));
	FAIL_ON(!mode.specified);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);
	FAIL_ON(mode.rotation_reflection != DRM_MODE_REFLECT_X);

	FAIL_ON(mode.refresh_specified);

	FAIL_ON(mode.bpp_specified);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.interlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.force != DRM_FORCE_UNSPECIFIED);

	return 0;
}

static int drm_cmdline_test_vmirror(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(!drm_mode_parse_command_line_for_connector("720x480,reflect_y",
							   &connector,
							   &mode));
	FAIL_ON(!mode.specified);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);
	FAIL_ON(mode.rotation_reflection != DRM_MODE_REFLECT_Y);

	FAIL_ON(mode.refresh_specified);

	FAIL_ON(mode.bpp_specified);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.interlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.force != DRM_FORCE_UNSPECIFIED);

	return 0;
}

static int drm_cmdline_test_margin_options(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(!drm_mode_parse_command_line_for_connector("720x480,margin_right=14,margin_left=24,margin_bottom=36,margin_top=42",
							   &connector,
							   &mode));
	FAIL_ON(!mode.specified);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);
	FAIL_ON(mode.tv_margins.right != 14);
	FAIL_ON(mode.tv_margins.left != 24);
	FAIL_ON(mode.tv_margins.bottom != 36);
	FAIL_ON(mode.tv_margins.top != 42);

	FAIL_ON(mode.refresh_specified);

	FAIL_ON(mode.bpp_specified);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.interlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.force != DRM_FORCE_UNSPECIFIED);

	return 0;
}

static int drm_cmdline_test_multiple_options(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(!drm_mode_parse_command_line_for_connector("720x480,rotate=270,reflect_x",
							   &connector,
							   &mode));
	FAIL_ON(!mode.specified);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);
	FAIL_ON(mode.rotation_reflection != (DRM_MODE_ROTATE_270 | DRM_MODE_REFLECT_X));

	FAIL_ON(mode.refresh_specified);

	FAIL_ON(mode.bpp_specified);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.interlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.force != DRM_FORCE_UNSPECIFIED);

	return 0;
}

static int drm_cmdline_test_invalid_option(void *ignored)
{
	struct drm_connector connector = { };
	struct drm_cmdline_mode mode = { };

	FAIL_ON(drm_mode_parse_command_line_for_connector("720x480,test=42",
							  &connector,
							  &mode));

	return 0;
}

#include "drm_selftest.c"

static int __init test_drm_cmdline_init(void)
{
	int err;

	err = run_selftests(selftests, ARRAY_SIZE(selftests), NULL);

	return err > 0 ? 0 : err;
}
module_init(test_drm_cmdline_init);

MODULE_AUTHOR("Maxime Ripard <maxime.ripard@bootlin.com>");
MODULE_LICENSE("GPL");
