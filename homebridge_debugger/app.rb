require 'sinatra'
require "sinatra/activerecord"
require "./models/config.rb"
set :database, "sqlite3:myblogdb.sqlite3"

require 'byebug'

Config.power_state.update_attributes(value: 0)

get '/getCurrentTemperature' do
  content_type :json
  {"value" => 18.18}.to_json
end

get '/getCurrentRelativeHumidity' do
  content_type :json
  {"value" => 60}.to_json
end

get '/getOn' do
  content_type :json
  {"value" => Config.power_state.value}.to_json
end

get '/setOn/:state' do
  Config.power_state.update_attributes(value: (params[:state] == "true" ? 1 : 0) )
  content_type :json
  {"value" => Config.power_state.value}.to_json
end
