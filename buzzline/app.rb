#!/usr/bin/env ruby

require 'logger'
require 'rubygems'

### Buzzline DB Application (incomplete)

## General setup routines

# Global variables (names and paths)
app_label = 'buzzline'
app_dir = File.dirname(__FILE__)
app_datadir = File.join(app_dir, 'var')
app_logdir = File.join(app_datadir, 'log')
# Database-specific variables
db_protocol = 'sqlite3'
db_slug = [ app_label, db_protocol ].join('.')
# Sinatra-specific variables
server_logfile = File.join(app_logdir, 'sinatra.log')
server_log = Logger.new(server_logfile, 'a+')
server_log.datetime_format = '%Y/%m/%d @ %H:%M:%S '
server_log.level = Logger::INFO

## DataMapper setup (TODO find DB protocol for Cedar w/o sqlite)

require 'dm-core'
require 'dm-sqlite-adapter'

# Open DB connection
DataMapper.setup(:default, "#{db_protocol}://#{app_datadir}/db/#{db_slug}")
# Start logging all events
DataMapper::Logger.new(File.join(app_logdir, "#{db_slug}.log"), :debug)

### Sinatra w/ HAML setup

require 'sinatra'
require 'haml'

## Sinatra configuration

# Main configuration block
configure do
	set :app_name, app_label.capitalize
	# Specify our main launcher
	set :app_file, __FILE__
	# Direct requests to the proper static files and/or templates
	set :public_folder, Proc.new { File.join(app_dir, 'static') }
	set :views, Proc.new { File.join(app_dir, 'templates') }
	# Listen on all interfaces for HTTP connections
	set :bind => '0.0.0.0', :port => 8080
	# Log to file by default
	enable :logging
	# Generate HTML5 valid markup using HAML
	set :haml, { :format => :html5, :attr_wrapper => '"' }
	# MIME type mappings
	mime_type :css, 'text/css'
	mime_type :ico, 'image/x-icon'
	mime_type :js,  'application/javascript'
end

# TODO alternate :production: :test: configurations?
configure :production do
	enable :protection
end
configure :development do
	disable :protection
	enable :dump_errors
end
configure :test do
	set :protection, :except => :path_traversal
end

## General URL matching rules

get '/' do
	redirect '/hello'
end

## Rules from tutorial

get '/hello' do
	redirect '/hello/world'
end

get '/hello/:thing' do
	@recipient = params[:thing].capitalize
	@app_name = settings.app_name
	haml :hello
end

## Buzzline rules

$LOAD_PATH << File.join(app_dir, 'lib')
require 'buzzline.model'

# Dump a list of all Buzzlines
get '/list' do
	haml :list, :locals => { :buzzlines => Buzzline.all }
end

# Redirect to login
get '/login' do
	redirect '/login/'
end

# Login prompt
get '/login/:id' do
	@username = params[:id]
	haml :login
end
