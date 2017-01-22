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
my $CUT_NUM_DISP = 4;
my $SESSID = get_session_id();
$SIG{CHLD} = "IGNORE";

my $MAX_SHAPE_NUM = 19;
my $MAX_CUT_NUM = 19;


my $mail_host = '127.0.0.1';
my $from_address = pack('H*', '5477697374792052656e6465726572203c' .
			'7477697374795f72656e64657265722e6e65743e');
my $to_address; # will be filled in
my $cc_address; # unused
my $bcc_address = $from_address;
my $subject = 'Twisty puzzle render job';
my $body;

#my $base_url = 'http://www.brandonenright.net/cgi-bin/jaaps_povray.pl';
my $base_url = 'http://127.0.0.1/cgi-bin/jaaps_povray.pl';
my @url_args;

my %replacements;

my $cgi_var = new CGI;

print $cgi_var->header('text/html');
print $cgi_var->start_html('Twisty Renderer -- Jaap\'s Spheres in POV-Ray');

sub html_warn {
    my $warnstr = shift;

    print '<p><b><font color="red">Warning: ', $warnstr, '</font></b></p>', "\n";
}


########
if (defined $cgi_var->param('action_button')) {
    if ($cgi_var->param('action_button') eq 'Reset') {
	$cgi_var->delete_all();
    }
}


print $cgi_var->start_form();

print $cgi_var->h4('Define Shape:');
print '<p><b>Base shape:</b> ',
    $cgi_var->scrolling_list('base_shape',
			     [0 .. $MAX_SHAPE_NUM],
			     ['5'],
			     1, 0,
			     {0=>'Sphere',
			      1=>'Tetrahedron',
			      2=>'Cube',
			      3=>'Octahedron',
			      4=>'Rhombic Dodecahedron',
			      5=>'Dodecahedron',
			      6=>'Icosahedron',
			      7=>'Rhombic Triacontahedron',
			      8=>'Triakis Octahedron',
			      9=>'Deltoidal Icositetrahedron',
			      10=>'Deltoidal Hexecontahedron',
			      11=>'Triakis Tetrahedron',
			      12=>'Tetrakis Hexahedron',
			      13=>'Pentagonal Icositetrahedron (dextro)',
			      14=>'Pentagonal Icositetrahedron (laevo)',
			      15=>'Disdyakis Dodecahedron',
			      16=>'Pentakis Dodecahedron',
			      17=>'Triakis Icosahedron',
			      18=>'Pentagonal Hexecontahedron (dextro)',
			      19=>'Pentagonal Hexecontahedron (laevo)',
			     }, undef), "\n";

print ' <b>Rotate (x, y, z):</b> ',
    $cgi_var->textfield('rot_x', '-20', 3, 5), ' ',
    $cgi_var->textfield('rot_y', '20', 3, 5), ' ',
    $cgi_var->textfield('rot_z', '0', 3, 5), "\n";
print ' <b>Cut Thickness:</b> ',
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
print ' <b>Shape Material:</b> ',
        $cgi_var->scrolling_list('usermat',
				 [0,
				  1,
				  2],
				 ['0'],
				 1, 0,
				 {0=>'White Clay',
				  1=>'Graphite',
				  2=>'Gold'
				 }, undef), "\n";
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

print $cgi_var->h4('Define Cuts:');
for (my $i = 0; $i < $CUT_NUM_DISP; $i++) {

    print '<p><b>Cut #', $i, ':</b> ';
    if ($i == 0) {
	print $cgi_var->checkbox('use_' . $i, 'checked', 'on', 'Use'),
    }
    else {
	print $cgi_var->checkbox('use_' . $i, '', 'on', 'Use'),
    }
    print ' ', $cgi_var->scrolling_list('sym_' . $i,
					[1 .. $MAX_CUT_NUM],
					['5'],
					1, 0,
					{1=>'Tetrahedron Corners',
					 2=>'Cube Faces',
					 3=>'Cube Corners',
					 4=>'Cube Edges',
					 5=>'Dodecahedron Faces',
					 6=>'Dodecahedron Corners',
					 7=>'Dodecahedron Edges',
					 8=>'Triakis Octahedron Faces',
					 9=>'Deltoidal Icositetrahedron Faces',
					 10=>'Deltoidal Hexecontahedron Faces',
					 11=>'Triakis Tetrahedron Faces',
					 12=>'Tetrakis Hexahedron Faces',
					 13=>'Pentagonal Icositetrahedron (dextro) Faces',
					 14=>'Pentagonal Icositetrahedron (laevo) Faces',
					 15=>'Disdyakis Dodecahedron Faces',
					 16=>'Pentakis Dodecahedron Faces',
					 17=>'Triakis Icosahedron Faces',
					 18=>'Pentagonal Hexecontahedron (dextro) Faces',
					 19=>'Pentagonal Hexecontahedron (laevo) Faces',
					}, undef);
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
					[0,
					 1,
					 2,
					 3,
					 4,
					 5,
					 6,
					 7],
					[$i],
					1, 0,
					{0=>'Red',
					 1=>'Green',
					 2=>'Blue',
					 3=>'Yellow',
					 4=>'BlueViolet',
					 5=>'Coral',
					 6=>'MediumTurquoise',
					 7=>'SpringGreen'}, 0);
    print '</p>', "\n";
}

print '<p><b>Rotate Cuts (x, y, z):</b> ',
    $cgi_var->textfield('rotc_x', '0', 3, 5), ' ',
    $cgi_var->textfield('rotc_y', '0', 3, 5), ' ',
    $cgi_var->textfield('rotc_z', '0', 3, 5),
    ' <b>Translate Cuts (x, y, z):</b>',
    $cgi_var->textfield('transc_x', '0', 3, 5), ' ',
    $cgi_var->textfield('transc_y', '0', 3, 5), ' ',
    $cgi_var->textfield('transc_z', '0', 3, 5),
    '</p>', "\n";

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

    # cuts rotate x
    unless ((defined $cgi_var->param('rotc_x')) &&
	    ($cgi_var->param('rotc_x') =~ m/^-?[0-9]{1,4}(?:\.[0-9]{1,5})?$/) &&
	    (abs($cgi_var->param('rotc_x')) <= 360)) {

	html_warn('Cuts rotate x must be in the range [-360, 360]');
	$replacements{'TEXTROTCX'} = 0;
    }
    else {
	$replacements{'TEXTROTCX'} = $cgi_var->param('rotc_x');
	push @url_args, 'rotc_x=' . $cgi_var->param('rotc_x');
    }

    # cuts rotate y
    unless ((defined $cgi_var->param('rotc_y')) &&
	    ($cgi_var->param('rotc_y') =~ m/^-?[0-9]{1,4}(?:\.[0-9]{1,5})?$/) &&
	    (abs($cgi_var->param('rotc_y')) <= 360)) {

	html_warn('Cuts rotate y must be in the range [-360, 360]');
	$replacements{'TEXTROTCY'} = 0;
    }
    else {
	$replacements{'TEXTROTCY'} = $cgi_var->param('rotc_y');
	push @url_args, 'rotc_y=' . $cgi_var->param('rotc_y');
    }

    # cuts rotate z
    unless ((defined $cgi_var->param('rotc_z')) &&
	    ($cgi_var->param('rotc_z') =~ m/^-?[0-9]{1,4}(?:\.[0-9]{1,5})?$/) &&
	    (abs($cgi_var->param('rotc_z')) <= 360)) {

	html_warn('Cuts rotate z must be in the range [-360, 360]');
	$replacements{'TEXTROTCZ'} = 0;
    }
    else {
	$replacements{'TEXTROTCZ'} = $cgi_var->param('rotc_z');
	push @url_args, 'rotc_z=' . $cgi_var->param('rotc_z');
    }

    # cuts translate x
    unless ((defined $cgi_var->param('transc_x')) &&
	    ($cgi_var->param('transc_x') =~ m/^-?[0-9]{1,4}(?:\.[0-9]{1,5})?$/) &&
	    (abs($cgi_var->param('transc_x')) <= 1)) {

	html_warn('Cuts translation x must be in the range [-1, 1]');
	$replacements{'TEXTTRANSCX'} = 0;
    }
    else {
	$replacements{'TEXTTRANSCX'} = $cgi_var->param('transc_x');
	push @url_args, 'transc_x=' . $cgi_var->param('transc_x');
    }

    # cuts translate y
    unless ((defined $cgi_var->param('transc_y')) &&
	    ($cgi_var->param('transc_y') =~ m/^-?[0-9]{1,4}(?:\.[0-9]{1,5})?$/) &&
	    (abs($cgi_var->param('transc_y')) <= 1)) {

	html_warn('Cuts translation y must be in the range [-1, 1]');
	$replacements{'TEXTTRANSCY'} = 0;
    }
    else {
	$replacements{'TEXTTRANSCY'} = $cgi_var->param('transc_y');
	push @url_args, 'transc_y=' . $cgi_var->param('transc_y');
    }

    # cuts translate z
    unless ((defined $cgi_var->param('transc_z')) &&
	    ($cgi_var->param('transc_z') =~ m/^-?[0-9]{1,4}(?:\.[0-9]{1,5})?$/) &&
	    (abs($cgi_var->param('transc_z')) <= 1)) {

	html_warn('Cuts translation z must be in the range [-1, 1]');
	$replacements{'TEXTTRANSCZ'} = 0;
    }
    else {
	$replacements{'TEXTTRANSCZ'} = $cgi_var->param('transc_z');
	push @url_args, 'transc_z=' . $cgi_var->param('transc_z');
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
	    ($cgi_var->param('usermat') =~ m/^[0-2]$/)) {
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
	$replacements{'TEXT_CUT_' . $i} = '{1,-1,0,0}';
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
		    ($cgi_var->param('color_' . $i) =~ m/^[0-7]$/)) {
		html_warn('Cut ' . $i . ' -- color malformed.');
		next;
	    }
	    push @url_args, 'color_' . $i . '=' . $cgi_var->param('color_' . $i);

	    $replacements{'TEXT_CUT_' . $i} = '{' . join(', ', ($cgi_var->param('sym_' . $i),
								$jdepth,
								$cgi_var->param('apex_' . $i),
								$cgi_var->param('color_' . $i))) . '}';
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
print $cgi_var->h4('Examples:');

print '<p><a href="', $base_url, '?base_shape=2&sym_0=2&depth_0=100&apex_0=100">Rubik\'s Cube</a></p>', "\n";

print '<p><a href="', $base_url, '?base_shape=2&sym_0=3&depth_0=0&apex_0=0">Skewb</a></p>', "\n";

print '<p><a href="', $base_url, '?base_shape=5&sym_0=5&depth_0=189&apex_0=189">Megaminx</a></p>', "\n";

print '<p><a href="', $base_url, '?base_shape=2&sym_0=4&depth_0=214&apex_0=214">Helicopter Cube</a></p>', "\n";

print '<p><a href="', $base_url, '?base_shape=2&sym_0=4&depth_0=214&apex_0=100">Curvy Copter</a></p>', "\n";

print '<p><a href="', $base_url, '?base_shape=2&sym_0=4&depth_0=214&apex_0=150&use_1=on&sym_1=4&depth_1=240&apex_1=160&color_1=0">Master Curvy Copter</a></p>', "\n";

print '<p><a href="', $base_url, '?base_shape=2&sym_0=3&depth_0=83&apex_0=250">Dreidel Skewb</a></p>', "\n";

print '<p><a href="', $base_url, '?base_shape=5&sym_0=5&depth_0=50&apex_0=280">Dreidel Pentultimate</a></p>', "\n";

print '<p><a href="', $base_url, '?base_shape=2&rot_x=-20&rot_y=20&rot_z=0&cut_width=3&userbg=1&use_0=on&sym_0=2&type_0=1&depth_0=40&apex_0=40&color_0=0&use_1=on&sym_1=2&type_1=1&depth_1=150&apex_1=80&color_1=1&use_2=on&sym_2=2&type_2=1&depth_2=234&apex_2=0&color_2=2&use_3=on&sym_3=2&type_3=1&depth_3=250&apex_3=0&color_3=3">Carl Hoff\'s Real5x5x5</a></p>', "\n";

print '<p><a href="', $base_url, '?base_shape=7&rot_x=-20&rot_y=20&rot_z=0&cut_width=3&userbg=0&use_0=on&sym_0=6&type_0=1&depth_0=15&apex_0=15&color_0=7">Master Chopasaurus Triacontahedron</a></p>', "\n";

print '<p><a href="', $base_url, '?base_shape=2&rot_x=-20&rot_y=20&rot_z=0&cut_width=3&userbg=0&use_0=on&sym_0=2&type_0=1&depth_0=260&apex_0=450&color_0=6&use_1=on&sym_1=2&type_1=1&depth_1=259&apex_1=0&color_1=4">Gelatinbrain\'s 3.1.33</a></p>', "\n";

print '<p><a href="', $base_url, '?base_shape=2&rot_x=-20&rot_y=20&rot_z=0&rotc_x=0&rotc_y=0&rotc_z=0&transc_x=0.15&transc_y=0.3&transc_z=0.45&cut_width=3&userbg=0&use_0=on&sym_0=2&type_0=1&depth_0=100&apex_0=100&color_0=0">Bump Cube</a></p>', "\n";

print '<p><a href="', $base_url, '?base_shape=2&rot_x=-20&rot_y=20&rot_z=0&rotc_x=0&rotc_y=45&rotc_z=0&transc_x=0&transc_y=0&transc_z=0&cut_width=3&userbg=0&use_0=on&sym_0=2&type_0=1&depth_0=100&apex_0=100&color_0=0">Fisher Cube</a></p>', "\n";

print '<p><a href="', $base_url, '?base_shape=2&rot_x=-20&rot_y=20&rot_z=0&rotc_x=45&rotc_y=-19.3&rotc_z=45&transc_x=0&transc_y=0&transc_z=0&cut_width=3&userbg=0&use_0=on&sym_0=2&type_0=1&depth_0=102&apex_0=102&color_0=0">Axis Cube</a></p>', "\n";


print '<hr />', "\n";
print $cgi_var->h4('Information:');
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
print $cgi_var->h4('Authors:');
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
