#!/usr/bin/perl

use strict;
use warnings;

use POSIX qw(setsid);
use MIME::Lite;
use CGI;

use Math::Trig;

# Change to the working directory
chdir('/var/www/localhost/htdocs/render_data/') or
    die 'Unable to change diretory: ', $?, "\n";


my $CUT_NUM = 8;
my $CUT_NUM_DISP = 5;
my $SESSID = get_session_id();
$SIG{CHLD} = "IGNORE";

my $mail_host = '127.0.0.1';
my $from_address = pack('H*', '5477697374792052656e64657265' .
			'72203c7477697374795f72656e64657265' .
			'72406272616e646f6e656e72696768742e6e65743e');
my $to_address; # will be filled in
my $cc_address; # unused
my $bcc_address = pack('H*', '7477697374795f72656e646572657' .
		       '2406272616e646f6e656e72696768742e6e6574');
my $subject = 'Twisty puzzle render job';
my $body;

#my $base_url = 'http://www.brandonenright.net/cgi-bin/jaaps_povray.pl';
my $base_url = 'http://127.0.0.1/cgi-bin/jaaps_povray.pl';
my @url_args;

my %replacements;


my $MAX_SHAPE_NUM = 65;
my $MAX_CUT_NUM = 46;
my $MAX_COLOR_NUM = 20;

# The shapes in order of appearance
my @shapes = (
    {('num' => -1, 'name' => '-- Smooth Solids --')},
    {('num' => 0, 'name' => 'Sphere')},
    {('num' => -2, 'name' => '-- Platonic Solids --')},
    {('num' => 1, 'name' => 'Tetrahedron')},
    {('num' => 2, 'name' => 'Cube')},
    {('num' => 3, 'name' => 'Octahedron')},
    {('num' => 5, 'name' => 'Dodecahedron')},
    {('num' => 6, 'name' => 'Icosahedron')},
    {('num' => -3, 'name' => '-- Catalan Solids --')},
    {('num' => 4, 'name' => 'Rhombic Dodecahedron')},
    {('num' => 7, 'name' => 'Rhombic Triacontahedron')},
    {('num' => 11, 'name' => 'Triakis Tetrahedron')},
    {('num' => 12, 'name' => 'Tetrakis Hexahedron')},
    {('num' => 8, 'name' => 'Triakis Octahedron')},
    {('num' => 17, 'name' => 'Triakis Icosahedron')},
    {('num' => 10, 'name' => 'Deltoidal Hexecontahedron')},
    {('num' => 9, 'name' => 'Deltoidal Icositetrahedron')},
    {('num' => 18, 'name' => 'Pentagonal Hexecontahedron (dextro)')},
    {('num' => 19, 'name' => 'Pentagonal Hexecontahedron (laevo)')},
    {('num' => 13, 'name' => 'Pentagonal Icositetrahedron (dextro)')},
    {('num' => 14, 'name' => 'Pentagonal Icositetrahedron (laevo)')},
    {('num' => 15, 'name' => 'Disdyakis Dodecahedron')},
    {('num' => 20, 'name' => 'Disdyakis Triacontahedron')},
    {('num' => 16, 'name' => 'Pentakis Dodecahedron')},
    {('num' => -4, 'name' => '-- Dipyramids --')},
    {('num' => 21, 'name' => 'Triangular Dipyramid')},
    {('num' => 22, 'name' => 'Pentagonal Dipyramid')},
    {('num' => 23, 'name' => 'Hexagonal Dipyramid')},
    {('num' => 24, 'name' => 'Heptagonal Dipyramid')},
    {('num' => 25, 'name' => 'Octagonal Dipyramid')},
    {('num' => -5, 'name' => '-- Trapezohedra --')},
    {('num' => 26, 'name' => 'Tetragonal Trapezohedron')},
    {('num' => 27, 'name' => 'Pentagonal Trapezohedron')},
    {('num' => 28, 'name' => 'Hexagonal Trapezohedron')},
    {('num' => 29, 'name' => 'Heptagonal Trapezohedron')},
    {('num' => 30, 'name' => 'Octagonal Trapezohedron')},
    {('num' => -6, 'name' => '-- Prisms and Antiprisms --')},
    {('num' => 56, 'name' => 'Triangular Prism (Square Sides)')},
    {('num' => 57, 'name' => 'Pentagonal Prism (Square Sides)')},
    {('num' => 58, 'name' => 'Hexagonal Prism (Square Sides)')},
    {('num' => 59, 'name' => 'Heptagonal Prism (Square Sides)')},
    {('num' => 60, 'name' => 'Octagonal Prism (Square Sides)')},
    {('num' => 61, 'name' => 'Square Antiprism')},
    {('num' => 62, 'name' => 'Pentagonal Antiprism')},
    {('num' => 63, 'name' => 'Hexagonal Antiprism')},
    {('num' => 64, 'name' => 'Heptagonal Antiprism')},
    {('num' => 65, 'name' => 'Octagonal Antiprism')},
    {('num' => 34, 'name' => 'Triangular Prism (Equidistant Faces)')},
    {('num' => 35, 'name' => 'Pentagonal Prism (Equidistant Faces)')},
    {('num' => 36, 'name' => 'Hexagonal Prism (Equidistant Faces)')},
    {('num' => 37, 'name' => 'Heptagonal Prism (Equidistant Faces)')},
    {('num' => 38, 'name' => 'Octagonal Prism (Equidistant Faces)')},
    {('num' => -7, 'name' => '-- Archimedean Solids --')},
    {('num' => 43, 'name' => 'Truncated Tetrahedron')},
    {('num' => 41, 'name' => 'Cuboctahedron')},
    {('num' => 45, 'name' => 'Truncated Cube')},
    {('num' => 48, 'name' => 'Snub Cube (dextro)')},
    {('num' => 49, 'name' => 'Snub Cube (laevo)')},
    {('num' => 46, 'name' => 'Rhombicuboctahedron')},
    {('num' => 44, 'name' => 'Truncated Octahedron')},
    {('num' => 47, 'name' => 'Truncated Cuboctahedron')},
    {('num' => 51, 'name' => 'Truncated Dodecahedron')},
    {('num' => 42, 'name' => 'Icosidodecahedron')},
    {('num' => 54, 'name' => 'Snub Dodecahedron (dextro)')},
    {('num' => 55, 'name' => 'Snub Dodecahedron (laevo)')},
    {('num' => 50, 'name' => 'Truncated Icosahedron')},
    {('num' => 52, 'name' => 'Rhombicosidodecahedron')},
    {('num' => 53, 'name' => 'Truncated Icosidodecahedron')},
    {('num' => -8, 'name' => '-- Other Solids --')},
    {('num' => 31, 'name' => 'Trapezo-Rhombic Dodecahedron')},
    {('num' => 32, 'name' => 'Pseudo-Deltoidal Icositetrahedron')},
    {('num' => 33, 'name' => 'Trapezo-Rhombic Triacontahedron')},
    {('num' => 39, 'name' => 'Truncated Cube (Equidistant Faces)')},
    {('num' => 40, 'name' => 'Truncated Dodecahedron (Equidistant Faces)')},
    );


# The cuts in order of appearance
my @cuts = (
    {('num' => -1, 'name' => '-- Platonic Geometries --')},
    {('num' => 1, 'name' => 'Tetrahedron')},
    {('num' => 41, 'name' => 'Tetrahedron (Corners)')},
    {('num' => 2, 'name' => 'Cube')},
    {('num' => 3, 'name' => 'Octahedron')},
    {('num' => 5, 'name' => 'Dodecahedron')},
    {('num' => 6, 'name' => 'Icosahedron')},
    {('num' => -2, 'name' => '-- Catalan Geometries --')},
    {('num' => 4, 'name' => 'Rhombic Dodecahedron')},
    {('num' => 7, 'name' => 'Rhombic Triacontahedron')},
    {('num' => 11, 'name' => 'Triakis Tetrahedron')},
    {('num' => 12, 'name' => 'Tetrakis Hexahedron')},
    {('num' => 8, 'name' => 'Triakis Octahedron')},
    {('num' => 17, 'name' => 'Triakis Icosahedron')},
    {('num' => 10, 'name' => 'Deltoidal Hexecontahedron')},
    {('num' => 9, 'name' => 'Deltoidal Icositetrahedron')},
    {('num' => 18, 'name' => 'Pentagonal Hexecontahedron (dextro)')},
    {('num' => 19, 'name' => 'Pentagonal Hexecontahedron (laevo)')},
    {('num' => 13, 'name' => 'Pentagonal Icositetrahedron (dextro)')},
    {('num' => 14, 'name' => 'Pentagonal Icositetrahedron (laevo)')},
    {('num' => 15, 'name' => 'Disdyakis Dodecahedron')},
    {('num' => 20, 'name' => 'Disdyakis Triacontahedron')},
    {('num' => 16, 'name' => 'Pentakis Dodecahedron')},
    {('num' => -3, 'name' => '-- Dipyramidal Geometries --')},
    {('num' => 21, 'name' => 'Triangular Dipyramid')},
    {('num' => 22, 'name' => 'Pentagonal Dipyramid')},
    {('num' => 23, 'name' => 'Hexagonal Dipyramid')},
    {('num' => 24, 'name' => 'Heptagonal Dipyramid')},
    {('num' => 25, 'name' => 'Octagonal Dipyramid')},
    {('num' => -4, 'name' => '-- Trapezohedral Geometries --')},
    {('num' => 26, 'name' => 'Tetragonal Trapezohedron')},
    {('num' => 27, 'name' => 'Pentagonal Trapezohedron')},
    {('num' => 28, 'name' => 'Hexagonal Trapezohedron')},
    {('num' => 29, 'name' => 'Heptagonal Trapezohedron')},
    {('num' => 30, 'name' => 'Octagonal Trapezohedron')},
    {('num' => -5, 'name' => '-- Prismatic Geometries --')},
    {('num' => 34, 'name' => 'Dihedral Cuts (Top & Bottom Faces)')},
    {('num' => 35, 'name' => 'Triangular Prism (Side Faces)')},
    {('num' => 36, 'name' => 'Square Prism (Side Faces)')},
    {('num' => 37, 'name' => 'Pentagonal Prism (Side Faces)')},
    {('num' => 38, 'name' => 'Hexagonal Prism (Side Faces)')},
    {('num' => 39, 'name' => 'Heptagonal Prism (Side Faces)')},
    {('num' => 40, 'name' => 'Octagonal Prism (Side Faces)')},
    {('num' => 42, 'name' => 'Square Antiprism (Side Faces)')},
    {('num' => 43, 'name' => 'Pentagonal Antiprism (Side Faces)')},
    {('num' => 44, 'name' => 'Hexagonal Antiprism (Side Faces)')},
    {('num' => 45, 'name' => 'Heptagonal Antiprism (Side Faces)')},
    {('num' => 46, 'name' => 'Octagonal Antiprism (Side Faces)')},
    {('num' => -6, 'name' => '-- Other Geometries --')},
    {('num' => 31, 'name' => 'Trapezo-Rhombic Dodecahedron')},
    {('num' => 32, 'name' => 'Pseudo-Deltoidal Icositetrahedron')},
    {('num' => 33, 'name' => 'Trapezo-Rhombic Triacontahedron')},
    );


my $cgi_var = new CGI;

print $cgi_var->header('text/html');
print $cgi_var->start_html('Twisty Renderer -- Jaap\'s Spheres in POV-Ray');

sub html_warn {
    my $warnstr = shift;

    print '<p><b><h3><font color="red">Warning: ', $warnstr,
    '</font></h3></b></p>', "\n";
}


########
if (defined $cgi_var->param('action_button')) {
    if ($cgi_var->param('action_button') eq 'Reset') {
	$cgi_var->delete_all();
    }
}


print $cgi_var->start_form();

print $cgi_var->h3('Define Shape:');
print '<p><b>Base shape:</b> ',
    $cgi_var->scrolling_list('base_shape',
			     [map {$_->{'num'}} @shapes],
			     ['5'],
			     1, 0,
			     {map {$_->{'num'} => $_->{'name'}} @shapes}, undef), "\n";

print ' <b>Shape Material:</b> ',
        $cgi_var->scrolling_list('usermat',
				 [0,
				  1,
				  2,
				  3,
				  4,
				  5],
				 ['0'],
				 1, 0,
				 {0=>'White Clay',
				  1=>'Graphite',
				  2=>'Gold',
      				  3=>'Pink Alabaster',
       				  4=>'White Marble',
       				  5=>'Polished Cherry Wood',
				 }, undef), "\n";
print '</p>', "\n";
print '<hr />', "\n";

print $cgi_var->h3('Define Scene:');

print '<p><b>Rotate Shape (x, y, z):</b> ',
    $cgi_var->textfield('rot_x', '-20', 3, 5), ' ',
    $cgi_var->textfield('rot_y', '25', 3, 5), ' ',
    $cgi_var->textfield('rot_z', '-8', 3, 5), "\n";

print ' <b>Background:</b> ',
        $cgi_var->scrolling_list('userbg',
				 [0,
				  1,
				  2],
				 ['0'],
				 1, 0,
				 {0=>'Black',
				  1=>'White',
				  2=>'Sky'}, undef), "\n";
print '</p>', "\n";
print '<hr />', "\n";

print $cgi_var->h3('Define Cuts:');

print '<p><b>Cut Thickness:</b> ',
        $cgi_var->scrolling_list('cut_width',
				 [1,
				  2,
				  3,
				  4,
				  5],
				 ['3'],
				 1, 0,
				 {1=>'1 (Thin)',
				  2=>'2',
				  3=>'3 (Normal)',
				  4=>'4',
				  5=>'5 (Thick)'}, undef), "\n";
print '</p>', "\n";

for (my $i = 0; $i < $CUT_NUM_DISP; $i++) {

    print '<p>--</p>', "\n";

    print '<p><b>Cut #', $i, ':</b> ';
    if ($i == 0) {
	print $cgi_var->checkbox('use_' . $i, 'checked', 'on', 'Use'),
    }
    else {
	print $cgi_var->checkbox('use_' . $i, '', 'on', 'Use'),
    }
    print ' ', $cgi_var->scrolling_list('sym_' . $i,
					[map {$_->{'num'}} @cuts],
					['5'],
					1, 0,
					{map {$_->{'num'} =>
						  $_->{'name'}} @cuts},
					undef);
    print ' at depth';
    print ' ', $cgi_var->textfield('depth_' . $i, '200', 7, 7);
    print ' ', $cgi_var->scrolling_list('type_' . $i,
					[1,
					 2],
					['1'],
					1, 0,
					{1=>'Jaap\'s [0 .. 300]',
					 2=>'Degrees from center [0 .. 90]'}, undef);
    print ' with apex at';
    print ' ', $cgi_var->textfield('apex_' . $i, '0', 5, 5);
    print ' ', $cgi_var->scrolling_list('color_' . $i,
					[0 .. $MAX_COLOR_NUM],
					[$i],
					1, 0,
					{0=>'Red',
					 1=>'Green',
					 2=>'Blue',
					 3=>'Yellow',
					 4=>'BlueViolet',
					 5=>'Coral',
					 6=>'MediumTurquoise',
					 7=>'SpringGreen',
					 8=>'Magenta',
					 9=>'Maroon',
					 10=>'YellowGreen',
					 11=>'Orange',
					 12=>'OrangeRed',
					 13=>'SeaGreen',
					 14=>'SummerSky',
					 15=>'NeonBlue',
					 16=>'White',
					 17=>'Black',
					 18=>'MediumSlateBlue',
					 19=>'MediumSpringGreen',
					 20=>'Scarlet',
					}, 0);
    print '</p>', "\n";

    print '<p><b>Rotate Cuts (x, y, z):</b> ',
    $cgi_var->textfield('rotc_x_' . $i, '0', 6, 8), ' ',
    $cgi_var->textfield('rotc_y_' . $i, '0', 6, 8), ' ',
    $cgi_var->textfield('rotc_z_' . $i, '0', 6, 8),
    ' <b>Translate Cuts (x, y, z):</b>',
    $cgi_var->textfield('transc_x_' . $i, '0', 6, 8), ' ',
    $cgi_var->textfield('transc_y_' . $i, '0', 6, 8), ' ',
    $cgi_var->textfield('transc_z_' . $i, '0', 6, 8),
    '</p>', "\n";
}

print '<hr />', "\n";
print $cgi_var->checkbox('zoomcam', '', 'on',
			 'Zoom camera for better precision'), "\n";
print '<p>', "\n";
print $cgi_var->submit('action_button', 'Fast Preview');
print ' ';
print $cgi_var->submit('action_button', 'Medium Preview');
print ' ';
print $cgi_var->submit('action_button', 'Slow Preview');
print '</p>', "\n";
print '<p>', "\n";
print $cgi_var->submit('action_button', 'Submit High Resolution Render Job'),
    ' <b>Email address to receive results (required):</b> ',
    $cgi_var->textfield('render_email', 'user@domain.com',
			20, 50);
print '</p>', "\n";
print '<hr />', "\n";
print $cgi_var->submit('action_button', 'Reset');
print $cgi_var->end_form();


if (defined $cgi_var->param('action_button')) {
    my $action = 'quick';



    if ($cgi_var->param('action_button') eq 'Fast Preview') {
	$action = 'fast';
    }
    if ($cgi_var->param('action_button') eq 'Medium Preview') {
	$action = 'medium';
    }
    if ($cgi_var->param('action_button') eq 'Slow Preview') {
	$action = 'slow';
    }
    if ($cgi_var->param('action_button') eq 'Submit High Resolution Render Job') {
	$action = 'job';
    }


    # Parse the base shape settings

    # base shape
    unless ((defined $cgi_var->param('base_shape')) &&
	    ($cgi_var->param('base_shape') =~ m/^[0-9]+$/) &&
	    (int($cgi_var->param('base_shape')) >= 0) &&
	    (int($cgi_var->param('base_shape')) <= $MAX_SHAPE_NUM)) {
	html_warn('Base shape malformed.');
	$replacements{'TEXTSHAPE'} = 5;
    }
    else {
	$replacements{'TEXTSHAPE'} = $cgi_var->param('base_shape');
	push @url_args, 'base_shape=' . $cgi_var->param('base_shape');
    }

    # rotate x
    unless ((defined $cgi_var->param('rot_x')) &&
	    ($cgi_var->param('rot_x') =~ m/^-?[0-9]{1,4}(?:\.[0-9]{1,5})?$/) &&
	    (abs($cgi_var->param('rot_x')) <= 360)) {

	html_warn('Rotate x must be in the range [-360, 360]');
	$replacements{'TEXTROTX'} = 20;
    }
    else {
	$replacements{'TEXTROTX'} = $cgi_var->param('rot_x');
	push @url_args, 'rot_x=' . $cgi_var->param('rot_x');
    }

    # rotate y
    unless ((defined $cgi_var->param('rot_y')) &&
	    ($cgi_var->param('rot_y') =~ m/^-?[0-9]{1,4}(?:\.[0-9]{1,5})?$/) &&
	    (abs($cgi_var->param('rot_y')) <= 360)) {

	html_warn('Rotate y must be in the range [-360, 360]');
	$replacements{'TEXTROTY'} = 20;
    }
    else {
	$replacements{'TEXTROTY'} = $cgi_var->param('rot_y');
	push @url_args, 'rot_y=' . $cgi_var->param('rot_y');
    }

    # rotate z
    unless ((defined $cgi_var->param('rot_z')) &&
	    ($cgi_var->param('rot_z') =~ m/^-?[0-9]{1,4}(?:\.[0-9]{1,5})?$/) &&
	    (abs($cgi_var->param('rot_z')) <= 360)) {

	html_warn('Rotate z must be in the range [-360, 360]');
	$replacements{'TEXTROTZ'} = 0;
    }
    else {
	$replacements{'TEXTROTZ'} = $cgi_var->param('rot_z');
	push @url_args, 'rot_z=' . $cgi_var->param('rot_z');
    }

    # Cut width
    unless ((defined $cgi_var->param('cut_width')) &&
	    ($cgi_var->param('cut_width') =~ m/^[1-5]$/)) {
	html_warn('Cut thickness malformed.');
	$replacements{'TEXTCUTWIDTH'} = '0.015';
    }
    else {
	$replacements{'TEXTCUTWIDTH'} = 0.005 * $cgi_var->param('cut_width');
	push @url_args, 'cut_width=' . $cgi_var->param('cut_width');
    }

    # Background
    unless ((defined $cgi_var->param('userbg')) &&
	    ($cgi_var->param('userbg') =~ m/^[0-2]$/)) {
	html_warn('Background malformed.');
	$replacements{'TEXTUSERBG'} = '0';
    }
    else {
	$replacements{'TEXTUSERBG'} = $cgi_var->param('userbg');
	push @url_args, 'userbg=' . $cgi_var->param('userbg');
    }

    # Material
    unless ((defined $cgi_var->param('usermat')) &&
	    ($cgi_var->param('usermat') =~ m/^[0-5]$/)) {
	html_warn('Material malformed.');
	$replacements{'TEXTUSERMAT'} = '0';
    }
    else {
	$replacements{'TEXTUSERMAT'} = $cgi_var->param('usermat');
	push @url_args, 'usermat=' . $cgi_var->param('usermat');
    }

    # Camera
    if ((defined $cgi_var->param('zoomcam')) &&
	($cgi_var->param('zoomcam') eq 'on')) {
	$replacements{'TEXTZOOMCAM'} = '1';
	push @url_args, 'zoomcam=' . $cgi_var->param('zoomcam');
    }
    else {
	$replacements{'TEXTZOOMCAM'} = '0';
    }

    #print 'got action: ', $action, "\n";

    for (my $i = 0; $i < $CUT_NUM; $i++) {
	$replacements{'TEXT_CUT_' . $i} = '{1, -1, 0, 0, 0, 0, 0, 0, 0, 0}';
	my $jdepth = 0;

	if ((defined $cgi_var->param('use_' . $i)) &&
	    ($cgi_var->param('use_' . $i) eq 'on')) {

	    push @url_args, 'use_' . $i . '=' . $cgi_var->param('use_' . $i);

	    unless ((defined $cgi_var->param('sym_' . $i)) &&
		    ($cgi_var->param('sym_' . $i) =~ m/^[0-9]+$/) &&
		    (int($cgi_var->param('sym_' . $i)) >= 1) &&
		    (int($cgi_var->param('sym_' . $i)) <= $MAX_CUT_NUM)) {
		html_warn('Cut ' . $i . ' -- symmetry malformed.');
		next;
	    }
	    push @url_args, 'sym_' . $i . '=' . $cgi_var->param('sym_' . $i);

	    unless ((defined $cgi_var->param('type_' . $i)) &&
		    ($cgi_var->param('type_' . $i) =~ m/^[12]$/)) {
		html_warn('Cut Type ' . $i . ' -- type not defined.');
		next;
	    }
	    push @url_args, 'type_' . $i . '=' . $cgi_var->param('type_' . $i);

	    if ($cgi_var->param('type_' . $i) == 1) {
		unless ((defined $cgi_var->param('depth_' . $i)) &&
			($cgi_var->param('depth_' . $i) =~ m/^[0-9]{1,4}(?:\.[0-9]{1,5})?$/) &&
			(abs($cgi_var->param('depth_' . $i)) <= 300)) {
		    #html_warn('got depth: ' . $cgi_var->param('depth_' . $i));
		    html_warn('Cut ' . $i . ' -- depth malformed (must be in the range [0, 300]).');
		    next;
		}
		$jdepth = abs($cgi_var->param('depth_' . $i));
	    }

	    if ($cgi_var->param('type_' . $i) == 2) {
		unless ((defined $cgi_var->param('depth_' . $i)) &&
			($cgi_var->param('depth_' . $i) =~ m/^[0-9]{1,4}(?:\.[0-9]{1,5})?$/) &&
			(abs($cgi_var->param('depth_' . $i)) <= 90)) {
		    #html_warn('got depth: ' . $cgi_var->param('depth_' . $i));
		    html_warn('Cut ' . $i . ' -- depth angle malformed (must be in the range [0, 90]).');
		    next;
		}
		$jdepth = sin(deg2rad(90.0 - abs($cgi_var->param('depth_' . $i)))) * 300.0;
	    }
	    push @url_args, 'depth_' . $i . '=' . $cgi_var->param('depth_' . $i);

	    unless ((defined $cgi_var->param('apex_' . $i)) &&
		    ($cgi_var->param('apex_' . $i) =~ m/^-?[0-9]{1,4}(?:\.[0-9]{1,5})?$/) &&
		    (abs($cgi_var->param('apex_' . $i)) <= 1000)) {
		html_warn('Cut ' . $i . ' -- apex malformed (must be in the range [-1000, 1000]).');
		next;
	    }
	    push @url_args, 'apex_' . $i . '=' . $cgi_var->param('apex_' . $i);

	    unless ((defined $cgi_var->param('color_' . $i)) &&
		    ($cgi_var->param('color_' . $i) =~ m/^[0-9]+$/) &&
		    (int($cgi_var->param('color_' . $i)) >= 0) &&
		    (int($cgi_var->param('color_' . $i)) <= $MAX_COLOR_NUM)) {
		html_warn('Cut ' . $i . ' -- color malformed.');
		next;
	    }
	    push @url_args, 'color_' . $i . '=' .
		$cgi_var->param('color_' . $i);

	    foreach my $dir ('x', 'y', 'z') {
		# cuts rotation per dir
		unless ((defined $cgi_var->param('rotc_' . $dir . '_' . $i)) &&
			($cgi_var->param('rotc_' . $dir . '_' . $i) =~
			 m/^-?[0-9]{1,4}(?:\.[0-9]{1,5})?$/) &&
			(abs($cgi_var->param('rotc_' . $dir . '_' . $i)) <=
			 360)) {

		    html_warn('Cuts rotate ' . $dir . ' must be in the range [-360, 360]');
		    next;
		}
		push @url_args, 'rotc_' . $dir . '_' . $i . '=' .
		    $cgi_var->param('rotc_' . $dir . '_' . $i);

		# Cuts translation per dir
		unless ((defined $cgi_var->param('transc_' . $dir . '_' . $i)) &&
			($cgi_var->param('transc_' . $dir . '_' . $i) =~
			 m/^-?[0-9](?:\.[0-9]{1,5})?$/) &&
			(abs($cgi_var->param('transc_' . $dir . '_' . $i)) <=
			 1)) {

		    html_warn('Cuts translation ' . $dir . ' must be in the range [-1, 1]');
		    next;
		}
		push @url_args, 'transc_' . $dir . '_' . $i . '=' .
		    $cgi_var->param('transc_' . $dir . '_' . $i);
	    }


	    $replacements{'TEXT_CUT_' . $i} =
		'{' . join(', ', (
			       $cgi_var->param('sym_' . $i),
			       $jdepth,
			       $cgi_var->param('apex_' . $i),
			       $cgi_var->param('color_' . $i),
			       $cgi_var->param('rotc_x_' . $i),
			       $cgi_var->param('rotc_y_' . $i),
			       $cgi_var->param('rotc_z_' . $i),
			       $cgi_var->param('transc_x_' . $i),
			       $cgi_var->param('transc_y_' . $i),
			       $cgi_var->param('transc_z_' . $i),
			   )) . '}';
	} # end if use
    } # end for each cut

    my $render_template;
    open(RENDERTEMPLATE, '<', 'render_template.txt') or
	die 'Unable to open render template: ', $?, ' ', $!, "\n";
    {
	local $/ = undef;
	$render_template  = <RENDERTEMPLATE>;
    }
    close RENDERTEMPLATE;


    # Do template replacements
    foreach my $replacement (keys %replacements) {
	$render_template =~ s/$replacement/$replacements{$replacement}/g;
    }

    open(POVOUT, '>', $SESSID . '.pov') or
	die 'Unable to open pov out: ', $?, ' ', $!, "\n";

    print POVOUT $render_template;

    close POVOUT;

    my $link = 0;
    if ($action eq 'fast') {
	print '<p><b>Fast preview:</b></p>', "\n";
	my $cmd = `./render_fast.sh $SESSID`;
	print '<img src="../render_data/fast_', $SESSID, '.png" />', "\n";
	$link = 1;
    }
    elsif ($action eq 'medium') {
	print '<p><b>Medium preview:</b></p>', "\n";
	my $cmd = `./render_medium.sh $SESSID`;
	print '<img src="../render_data/medium_', $SESSID, '.png" />', "\n";
	$link = 1;
    }
    elsif ($action eq 'slow') {
	print '<p><b>Slow preview:</b></p>', "\n";
	my $cmd = `./render_slow.sh $SESSID`;
	print '<img src="../render_data/slow_', $SESSID, '.png" />', "\n";
	$link = 1;
    }
    elsif ($action eq 'job') {

	unless ((defined $cgi_var->param('render_email')) &&
		($cgi_var->param('render_email') =~ m/^[\w\d._-]{1,40}@[\w\d.-]{3,80}$/) &&
		($cgi_var->param('render_email') ne 'user@domain.com')) {

	    html_warn('You must provide a valid email address for the render results to be sent to you.');
	}
	else {

	    $to_address = $cgi_var->param('render_email');
	    $subject .= ' ' . $SESSID;

	    if (fork() == 0) {
		# I'm the child
		close STDOUT;
		close STDIN;
		close STDERR;
		my $sess_id = POSIX::setsid();

		my $cmd = `./render_quality.sh $SESSID`;


		$body = 'Your rendered image for session ' . $SESSID .
		    ' is attached.' . "\n" . 'URL for configuration: ' .
		    $base_url . '?' . join('&', @url_args) . "\n";

		my $msg;
		### Create the multipart container
		$msg = MIME::Lite->new(
		    'From' => $from_address,
		    'To' => $to_address,
		    'Bcc' => $bcc_address,
		    'Subject' => $subject,
		    'Type' => 'text/plain',
		    'Data' => $body
		    ) or die 'Error creating multipart container: ', $!, "\n";

		$msg->attach(
		    'Type' => 'image/png',
		    'Path' => '../render_data/job_' . $SESSID . '.png',
		    'Filename' => $SESSID . '.png',
		    'Disposition' => 'attachment'
		    ) or die 'Error attaching image!',  $!, "\n";

		### Send the Message
		MIME::Lite->send('smtp', $mail_host, 'Timeout'=>10);
		$msg->send;

		exit(0);
	    }

	    print '<p><b><font color="#0000ff"><h1>A render job has been submitted',
	    ' and the results will be emailed to you.  Please allow at least an hour for the render to complete.</h1></font></b></p>', "\n";
	    $link = 1;
	}

    }

    if ($link == 1) {
	print '<p><a href="', $base_url, '?', join('&', @url_args), '">',
	'Link to current configuration.</a></p>', "\n";
    }
}

print '<hr />', "\n";
print $cgi_var->h3('Examples:');

print '<p><a href="', $base_url, '?base_shape=2&sym_0=2&depth_0=100&apex_0=100">Rubik\'s Cube</a></p>', "\n";

print '<p><a href="', $base_url, '?base_shape=2&sym_0=3&depth_0=0&apex_0=0">Skewb</a></p>', "\n";

print '<p><a href="', $base_url, '?base_shape=5&sym_0=5&depth_0=189&apex_0=189">Megaminx</a></p>', "\n";

print '<p><a href="', $base_url, '?base_shape=2&sym_0=4&depth_0=214&apex_0=214">Helicopter Cube</a></p>', "\n";

print '<p><a href="', $base_url, '?base_shape=2&sym_0=4&depth_0=214&apex_0=100">Curvy Copter</a></p>', "\n";

print '<p><a href="', $base_url, '?base_shape=2&sym_0=4&depth_0=214&apex_0=150&use_1=on&sym_1=4&depth_1=240&apex_1=160&color_1=0">Master Curvy Copter</a></p>', "\n";

print '<p><a href="', $base_url, '?base_shape=2&sym_0=3&depth_0=83&apex_0=250">Dreidel Skewb</a></p>', "\n";

print '<p><a href="', $base_url, '?base_shape=5&sym_0=5&depth_0=50&apex_0=280">Dreidel Pentultimate</a></p>', "\n";

print '<p><a href="', $base_url, '?base_shape=2&cut_width=3&userbg=1&use_0=on&sym_0=2&type_0=1&depth_0=40&apex_0=40&color_0=0&use_1=on&sym_1=2&type_1=1&depth_1=150&apex_1=80&color_1=1&use_2=on&sym_2=2&type_2=1&depth_2=234&apex_2=0&color_2=2&use_3=on&sym_3=2&type_3=1&depth_3=250&apex_3=0&color_3=3">Carl Hoff\'s Real5x5x5</a></p>', "\n";

print '<p><a href="', $base_url, '?base_shape=7&cut_width=3&userbg=0&use_0=on&sym_0=6&type_0=1&depth_0=15&apex_0=15&color_0=7">Master Chopasaurus Triacontahedron</a></p>', "\n";

print '<p><a href="', $base_url, '?base_shape=2&cut_width=3&userbg=0&use_0=on&sym_0=2&type_0=1&depth_0=260&apex_0=450&color_0=6&use_1=on&sym_1=2&type_1=1&depth_1=259&apex_1=0&color_1=4">Gelatinbrain\'s 3.1.33</a></p>', "\n";

print '<p><a href="', $base_url, '?base_shape=2&transc_x_0=0.15&transc_y_0=0.3&transc_z_0=0.45&cut_width=3&userbg=0&use_0=on&sym_0=2&type_0=1&depth_0=100&apex_0=100&color_0=0">Bump Cube</a></p>', "\n";

print '<p><a href="', $base_url, '?base_shape=2&rotc_x_0=0&rotc_y_0=45&rotc_z_0=0&cut_width=3&userbg=0&use_0=on&sym_0=2&type_0=1&depth_0=100&apex_0=100&color_0=0">Fisher Cube</a></p>', "\n";

print '<p><a href="', $base_url, '?base_shape=2&rotc_x_0=45&rotc_y_0=-19.3&rotc_z_0=45&cut_width=3&userbg=0&use_0=on&sym_0=2&type_0=1&depth_0=102&apex_0=102&color_0=0">Axis Cube</a></p>', "\n";

print '<p><a href="', $base_url, '?base_shape=2&rotc_x_0=90&rotc_y_0=125.3&rotc_z_0=135&cut_width=3&userbg=0&use_0=on&sym_0=21&type_0=1&depth_0=161&apex_0=161&color_0=19">David Pitcher\'s Insanity Cubed</a></p>', "\n";

print '<p><a href="', $base_url, '?base_shape=21&rot_x=-20&rot_y=25&rot_z=-8&cut_width=3&userbg=0&usermat=0&use_0=on&sym_0=21&type_0=1&depth_0=151&apex_0=151&color_0=18&rotc_x_0=0&transc_x_0=0&rotc_y_0=60&transc_y_0=0&rotc_z_0=0&transc_z_0=0&use_1=on&sym_1=35&type_1=1&depth_1=102&apex_1=102&color_1=18&rotc_x_1=0&transc_x_1=0&rotc_y_1=0&transc_y_1=0&rotc_z_1=0&transc_z_1=0">David Pitcher\'s Ultimate Insanity</a></p>', "\n";


print '<hr />', "\n";
print $cgi_var->h3('Information:');
print '<p>', "\n";
print 'The cuts are generated by a cone which allows for a range of ',
    'curvy or planar cuts.  The default (Jaap\'s) depth ranges from 0 (deep ',
    'cut) to 300 (shallowest cut).  The default cone apex is the center of ',
    'of the puzzle (0) which creates curvy cuts whenever the depth isn\'t ',
    'also set to 0.  You get a planar cut whenever the depth and the apex ',
    'are set to the same amount.  The apex units are always Jaap\'s depth so ',
    'if you use degrees for the cut it will be hard to achieve perfectly ',
    'planar cuts without doing some math to figure out what depth the ',
    'degrees work out to.', "\n";
print '</p>', "\n";
print '<img src="../render_data/render_cone_apex.png" />', "\n";

print '<p>', "\n";
print 'To prevent interference with the solid when the apex is outside of ',
    'the puzzle (outside of the range [-300, 300]) clipping is used.', "\n";
print '</p>', "\n";
print '<img src="../render_data/render_cone_clipping.png" />', "\n";

print '<hr />', "\n";
print $cgi_var->h3('Authors:');
print '<p>Twisty Renderer is based on Jaap Scherphuis\'s ',
    '<a href="http://www.jaapsch.net/puzzles/sphere.htm">',
    'Sphere Symmetry Applet</a>.  The POV-Ray code to do the rendering is ',
    'written by <a href="http://twistypuzzles.com/forum/memberlist.php',
    '?mode=viewprofile&u=6109">Stef-n</a>.  The web interface is ',
    'by Brandon Enright.</p>', "\n";
print '<p>All bugs, inqueries, and complaints should be directed to Brandon ',
    'at &lt;twisty_renderer atsymbol brandonenright.net&gt;</p>', "\n";
print '<hr />', "\n";
print '<p>Session id: ', $SESSID, '</p>', "\n";
print $cgi_var->end_html();


sub get_session_id {

    open(URANDOM, '<', '/dev/urandom') or die 'Unable to open urandom: ', $?, "\n";

    my $rand;
    read(URANDOM, $rand, 16);

    close URANDOM;

    return unpack('H*', $rand);
}
