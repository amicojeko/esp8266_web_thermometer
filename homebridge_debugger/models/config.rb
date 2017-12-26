#models.rb
class Config < ActiveRecord::Base
  class << self
    def power_state
      find_or_create_by(key: 'power_state')
    end
  end
end
